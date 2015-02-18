/*
 *  Copyright 2010-2015 Fabric Software Inc. All rights reserved.
 */

#include "SplitSearch.hpp"

#include <ctype.h>
#include <llvm/ADT/ArrayRef.h>
#include <llvm/ADT/StringMap.h>
#include <llvm/ADT/SmallString.h>
#include <stdint.h>
#include <vector>

namespace FabricServices { namespace SplitSearch { namespace Impl {

template<typename ArrayTy>
void SplitDelimitedString(
  llvm::StringRef delimitedStr,
  char delimiter,
  ArrayTy &result
  )
{
  std::pair<llvm::StringRef, llvm::StringRef> split(
    llvm::StringRef(), delimitedStr
    );
  while ( !split.second.empty() )
  {
    split = split.second.split( delimiter );
    result.push_back( split.first );
  }
}

static inline unsigned CommonSuffixLength(
  llvm::StringRef lhs,
  llvm::StringRef rhs
  )
{
  unsigned length = 0;
  for (;;)
  {
    if ( length >= lhs.size()
      || length >= rhs.size()
      || tolower( lhs[lhs.size()-length-1] )
        != tolower( rhs[rhs.size()-length-1] ) )
      break;
    ++length;
  }
  return length;
}

static inline unsigned RevMatch(
  llvm::StringRef haystack,
  llvm::StringRef needle
  )
{
  unsigned best = 0;
  while ( best < needle.size() && best < haystack.size() )
  {
    unsigned commonSuffixLength = CommonSuffixLength( haystack, needle );
    if ( commonSuffixLength > best )
      best = commonSuffixLength;
    haystack = haystack.drop_back();
  }
  return best;
}

static inline uint64_t Score(
  llvm::ArrayRef<llvm::StringRef> prefixes,
  llvm::StringRef needle
  )
{
  if ( !needle.empty() && !prefixes.empty() )
  {
    unsigned revMatch = RevMatch( prefixes.back(), needle );

    llvm::StringRef subNeedle = needle.drop_back( revMatch );
    llvm::ArrayRef<llvm::StringRef> subPrefixes = prefixes.drop_back();
    uint64_t subScore = Score( subPrefixes, subNeedle );

    if ( revMatch )
    {
      uint64_t score = needle.size() - revMatch + 1;
      if ( subScore != UINT64_MAX )
        score += 256 * subScore;
      return score;
    }
    else if ( subScore != UINT64_MAX )
      return 256 * subScore;
    else
      return UINT64_MAX;
  }
  else return UINT64_MAX;
}

class Match
{
  void const *m_userdata;
  uint64_t m_score;

public:

  Match( void const *userdata, unsigned score ) :
    m_userdata( userdata ), m_score( score ) {}

  void const *getUserdata() const { return m_userdata; }

  struct LessThan
  {
    bool operator()( Match const &lhs, Match const &rhs )
    {
      return lhs.m_score < rhs.m_score;
    }
  };
};

class Shareable
{
  unsigned _refCount;

protected:

  Shareable() : _refCount( 1 ) {}
  virtual ~Shareable() {}

public:

  void retain()
  {
    ++_refCount;
  }

  void release()
  {
    if ( --_refCount == 0 )
      delete this;
  }
};

class Matches : public Shareable
{
  std::vector<Match> m_impl;

  Matches( Matches const & ) = delete;
  Matches &operator=( Matches const & ) = delete;

protected:

  virtual ~Matches() {}

public:

  Matches() {}

  void add( void const *userdata, unsigned score )
  {
    m_impl.push_back( Match( userdata, score ) );
  }

  void sort() { std::sort( m_impl.begin(), m_impl.end(), Match::LessThan() ); }

  unsigned getSize() const { return m_impl.size(); }

  unsigned getUserdatas(
    unsigned max,
    void const **userdatas
    ) const
  {
    unsigned index = 0;
    while ( index < max && index < m_impl.size() )
    {
      userdatas[index] = m_impl[index].getUserdata();
      ++index;
    }
    return index;
  }
};

static inline llvm::ArrayRef<llvm::StringRef> DropFront(
  llvm::ArrayRef<llvm::StringRef> strs
  )
{
  return llvm::ArrayRef<llvm::StringRef>( strs.begin() + 1, strs.end() );
}

class Node
{
  void const *m_userdata;
  llvm::StringMap< std::unique_ptr<Node> > m_children;

protected:

  void search(
    llvm::SmallVector<llvm::StringRef, 8> &prefixes,
    llvm::StringRef needle,
    Matches *matches
    ) const
  {
    for ( llvm::StringMap< std::unique_ptr<Node> >::const_iterator it =
      m_children.begin(); it != m_children.end(); ++it )
    {
      prefixes.push_back( it->first() );

      if ( it->second->m_userdata )
      {
        uint64_t score = Score( prefixes, needle );
        if ( score != UINT64_MAX )
          matches->add( it->second->m_userdata, score );
      }

      std::unique_ptr<Node> const &node = it->second;
      node->search( prefixes, needle, matches );

      prefixes.pop_back();
    }
  }

public:

  Node( void *userdata ) : m_userdata( userdata ) {}
  Node( Node const & ) = delete;
  Node &operator=( Node const & ) = delete;
  ~Node() {}

  bool add(
    llvm::ArrayRef<llvm::StringRef> strs,
    void const *userdata
    )
  {
    if ( !strs.empty() )
    {
      std::unique_ptr<Node> &child = m_children[strs.front()];
      if ( !child )
        child = std::unique_ptr<Node>( new Node( nullptr ) );
      return child->add( DropFront( strs ), userdata );
    }
    else
    {
      if ( !m_userdata )
        m_userdata = userdata;
      return m_userdata == userdata;
    }
  }

  bool remove(
    llvm::ArrayRef<llvm::StringRef> strs,
    void const *userdata
    )
  {
    if ( !strs.empty() )
    {
      std::unique_ptr<Node> &child = m_children[strs.front()];
      if ( !child )
        return false;
      return child->remove( DropFront( strs ), userdata );
    }
    else
    {
      bool result = m_userdata == userdata;
      m_userdata = nullptr;
      return result;
    }
  }

  void clear()
  {
    m_children.clear();
  }

  void search(
    llvm::StringRef needle,
    Matches *matches
    ) const
  {
    llvm::SmallVector<llvm::StringRef, 8> prefixes;
    search( prefixes, needle, matches );
  }
};

class Dict : public Shareable
{
  Node m_root;

  Dict( Dict const & ) = delete;
  Dict &operator=( Dict const & ) = delete;

protected:

  virtual ~Dict() {}

public:

  Dict() : m_root( nullptr ) {}

  bool add(
    llvm::ArrayRef<llvm::StringRef> strs,
    void const *userdata
    )
  {
    return m_root.add( strs, userdata );
  }

  bool remove(
    llvm::ArrayRef<llvm::StringRef> strs,
    void const *userdata
    )
  {
    return m_root.remove( strs, userdata );
  }

  void clear()
  {
    m_root.clear();
  }

  Matches *search( llvm::StringRef needle ) const
  {
    Matches *matches = new Matches;
    m_root.search( needle, matches );
    matches->sort();
    return matches;
  }
};

} } }

using namespace FabricServices::SplitSearch::Impl;

FABRICSERICES_SPLITSEARCH_DECL
void FabricServices_SplitSearch_Matches_Retain(
  FabricServices_SplitSearch_Matches _matches
  )
{
  Matches *matches = static_cast<Matches *>( _matches );
  matches->retain();
}

FABRICSERICES_SPLITSEARCH_DECL
void FabricServices_SplitSearch_Matches_Release(
  FabricServices_SplitSearch_Matches _matches
  )
{
  Matches *matches = static_cast<Matches *>( _matches );
  matches->release();
}

FABRICSERICES_SPLITSEARCH_DECL
unsigned FabricServices_SplitSearch_Matches_GetSize(
  FabricServices_SplitSearch_Matches _matches
  )
{
  Matches *matches = static_cast<Matches *>( _matches );
  return matches->getSize();
}

FABRICSERICES_SPLITSEARCH_DECL
unsigned FabricServices_SplitSearch_Matches_GetUserdatas(
  FabricServices_SplitSearch_Matches _matches,
  unsigned max,
  void const **userdatas
  )
{
  Matches *matches = static_cast<Matches *>( _matches );
  return matches->getUserdatas( max, userdatas );
}

FABRICSERICES_SPLITSEARCH_DECL
FabricServices_SplitSearch_Dict FabricServices_SplitSearch_Dict_Create()
{
  return new Dict;
}

FABRICSERICES_SPLITSEARCH_DECL
bool FabricServices_SplitSearch_Dict_Add(
  FabricServices_SplitSearch_Dict _dict,
  unsigned numCStrs,
  char const * const *cStrs,
  void const *userdata
  )
{
  Dict *dict = static_cast<Dict *>( _dict );
  llvm::SmallVector<llvm::StringRef, 8> strs;
  while ( numCStrs-- > 0 )
    strs.push_back( *cStrs++ );
  return dict->add( strs, userdata );
}

FABRICSERICES_SPLITSEARCH_DECL
bool FabricServices_SplitSearch_Dict_Add_Delimited(
  FabricServices_SplitSearch_Dict _dict,
  char const *delimitedCStr,
  char delimiter,
  void const *userdata
  )
{
  Dict *dict = static_cast<Dict *>( _dict );
  llvm::SmallVector<llvm::StringRef, 8> strs;
  SplitDelimitedString( delimitedCStr, delimiter, strs );
  return dict->add( strs, userdata );
}

FABRICSERICES_SPLITSEARCH_DECL
bool FabricServices_SplitSearch_Dict_Remove(
  FabricServices_SplitSearch_Dict _dict,
  unsigned numCStrs,
  char const * const *cStrs,
  void const *userdata
  )
{
  Dict *dict = static_cast<Dict *>( _dict );
  llvm::SmallVector<llvm::StringRef, 8> strs;
  while ( numCStrs-- > 0 )
    strs.push_back( *cStrs++ );
  return dict->remove( strs, userdata );
}

FABRICSERICES_SPLITSEARCH_DECL
bool FabricServices_SplitSearch_Dict_Remove_Delimited(
  FabricServices_SplitSearch_Dict _dict,
  char const *delimitedCStr,
  char delimiter,
  void const *userdata
  )
{
  Dict *dict = static_cast<Dict *>( _dict );
  llvm::SmallVector<llvm::StringRef, 8> strs;
  SplitDelimitedString( delimitedCStr, delimiter, strs );
  return dict->remove( strs , userdata );
}

FABRICSERICES_SPLITSEARCH_DECL
void FabricServices_SplitSearch_Dict_Clear(
  FabricServices_SplitSearch_Dict _dict
  )
{
  Dict *dict = static_cast<Dict *>( _dict );
  dict->clear();
}

FABRICSERICES_SPLITSEARCH_DECL
FabricServices_SplitSearch_Matches FabricServices_SplitSearch_Dict_Search(
  FabricServices_SplitSearch_Dict _dict,
  char const *cStr
  )
{
  Dict *dict = static_cast<Dict *>( _dict );
  return dict->search( cStr );
}

FABRICSERICES_SPLITSEARCH_DECL
void FabricServices_SplitSearch_Dict_Retain(
  FabricServices_SplitSearch_Dict _dict
  )
{
  Dict *dict = static_cast<Dict *>( _dict );
  dict->retain();
}

FABRICSERICES_SPLITSEARCH_DECL
void FabricServices_SplitSearch_Dict_Release(
  FabricServices_SplitSearch_Dict _dict
  )
{
  Dict *dict = static_cast<Dict *>( _dict );
  dict->release();
}
