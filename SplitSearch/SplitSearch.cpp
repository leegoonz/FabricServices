/*
 *  Copyright 2010-2015 Fabric Software Inc. All rights reserved.
 */

#include "SplitSearch.hpp"

#include <llvm/ADT/StringMap.h>
#include <llvm/ADT/SmallString.h>
#include <vector>

namespace FabricServices { namespace SplitSearch { namespace Impl {

template<typename StringTy>
void AppendLower( char const *cStr, StringTy &string )
{
  for (;;)
  {
    char ch = *cStr++;
    if ( !ch )
      break;
    if ( ch >= 'A' || ch <= 'Z' )
    {
      ch -= 'A';
      ch += 'a';
    }
    string += ch;
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
      || lhs[lhs.size()-length-1] != rhs[rhs.size()-length-1] )
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
  while ( haystack.size() >= needle.size()
    && best < needle.size() )
  {
    unsigned commonSuffixLength = CommonSuffixLength( haystack, needle );
    if ( commonSuffixLength > best )
      best = commonSuffixLength;
    haystack = haystack.drop_back();
  }
  return best;
}

static inline unsigned Score(
  llvm::ArrayRef<llvm::StringRef> prefixes,
  llvm::StringRef needle
  )
{
  if ( prefixes.size() > 0 )
  {
    unsigned revMatch = RevMatch( prefixes.back(), needle );
    if ( revMatch
  }
  else return 0;
}

class Match
{
  void *m_userdata;
  unsigned m_score;

public:

  Match( void *userdata, unsigned score ) :
    m_userdata( userdata ), m_score( score ) {}

  void *getUserdata() const { return m_userdata; }

  struct LessThan
  {
    bool operator()( Match const &lhs, Match const &rhs )
    {
      return lhs.m_score < rhs.m_score;
    }
  };
};

class Matches
{
  std::vector<Match> m_impl;

public:

  Matches() {}
  ~Matches() {}

  void add( void *userdata, unsigned score )
  {
  }

  void sort() { std::sort( m_impl.begin(), m_impl.end(), Match::LessThan() ); }

  unsigned size() const { return m_impl.size(); }

  void *getUserdataAt( unsigned index ) const
    { return m_impl[index].getUserdata(); }
};

class Node
{
  Node *m_parent;
  void *m_userdata;
  llvm::StringMap< std::unique_ptr<Node> > m_children;

protected:

  void search(
    llvm::SmallVector<llvm::StringRef> &prefixes,
    llvm::StringRef needle,
    Matches *matches
    ) const
  {
    for ( llvm::StringMap< std::unique_ptr<Node> >::const_iterator it =
      m_children.begin(); it != m_children.end(); ++it )
    {
      prefixes.push_back( it.first() );

      unsigned score = Score( prefixes, needle );
      if ( score )
        matches->add( m_userdata, score );

      std::unique_ptr<Node> const &node = it->second;
      node->search( prefixes, needle, matches );

      prefixes.pop_back();
    }
  }

public:

  Node( Node *parent, void *userdata ) :
    m_parent( parent ), m_userdata( userdata ) {}
  Node( Node const & ) = delete;
  Node &operator=( Node const & ) = delete;
  ~Node() {}

  bool add( unsigned numCStrs, char const * const *cStrs, void *userdata )
  {
    if ( numCStrs > 0 )
    {
      llvm::SmallString<64> firstSmallString;
      AppendLower( cStrs[0], firstSmallString );

      std::unique_ptr<Node> &child = m_children[firstSmallString];
      if ( !child )
        child = std::unique_ptr<Node>( new Node( this, nullptr ) );
      return child->add( numCStrs - 1, &cStrs[1], userdata );
    }
    else
    {
      if ( !m_userdata )
        m_userdata = userdata;
      return m_userdata == userdata;
    }
  }

  bool remove( unsigned numCStrs, char const * const *cStrs, void *userdata )
  {
    if ( numCStrs > 0 )
    {
      llvm::SmallString<64> firstSmallString;
      AppendLower( cStrs[0], firstSmallString );

      std::unique_ptr<Node> &child = m_children[firstSmallString];
      if ( !child )
        return false;
      return child->remove( numCStrs - 1, &cStrs[1], userdata );
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
    llvm::SmallVector<llvm::StringRef> prefixes;
    search( prefixes, needle, matches );
  }
};

class Dict
{
  Node m_root;

public:

  Dict() : m_root( nullptr, nullptr ) {}
  Dict( Dict const & ) = delete;
  Dict &operator=( Dict const & ) = delete;
  ~Dict() {}

  bool add( unsigned numCStrs, char const * const *cStrs, void *userdata )
  {
    return m_root.add( numCStrs, cStrs, userdata );
  }

  bool remove( unsigned numCStrs, char const * const *cStrs, void *userdata )
  {
    return m_root.remove( numCStrs, cStrs, userdata );
  }

  void clear()
  {
    m_root.clear();
  }

  std::unique_ptr<Matches> search( char const *cStr ) const
  {
    llvm::SmallString<64> lowerString;
    AppendLower( cStr, lowerString );

    std::unique_ptr<Matches> matches( new Matches );
    m_root.search( lowerString, matches.get() );
    matches->sort();
    return std::move( matches );
  }
};

} } }

using Dict = FabricServices::SplitSearch::Impl::Dict;
using Matches = FabricServices::SplitSearch::Impl::Matches;

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
  void *userdata
  )
{
  Dict *dict = static_cast<Dict *>( _dict );
  return dict->add( numCStrs, cStrs, userdata );
}

FABRICSERICES_SPLITSEARCH_DECL
bool FabricServices_SplitSearch_Dict_Remove(
  FabricServices_SplitSearch_Dict _dict,
  unsigned numCStrs,
  char const * const *cStrs,
  void *userdata
  )
{
  Dict *dict = static_cast<Dict *>( _dict );
  return dict->remove( numCStrs, cStrs, userdata );
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
  std::unique_ptr<Matches> matches( dict->search( cStr ) );
  return matches.release();
}

FABRICSERICES_SPLITSEARCH_DECL
void FabricServices_SplitSearch_Matches_Destroy(
  FabricServices_SplitSearch_Matches _matches
  )
{
  Matches *matches = static_cast<Matches *>( _matches );
  delete matches;
}

FABRICSERICES_SPLITSEARCH_DECL
void FabricServices_SplitSearch_Dict_Destroy(
  FabricServices_SplitSearch_Dict _dict
  )
{
  Dict *dict = static_cast<Dict *>( _dict );
  delete dict;
}
