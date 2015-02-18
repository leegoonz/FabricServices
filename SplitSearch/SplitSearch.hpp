/*
 *  Copyright 2010-2015 Fabric Software Inc. All rights reserved.
 */

#ifndef _FABRIC_SplitSearch_hpp
#define _FABRIC_SplitSearch_hpp

#if defined(_MSC_VER) || defined(SWIGWIN)
# if defined(__cplusplus)
#  define FABRICSERICES_SPLITSEARCH_IMPORT extern "C" __declspec(dllimport)
#  define FABRICSERICES_SPLITSEARCH_EXPORT extern "C" __declspec(dllexport)
# else
#  define FABRICSERICES_SPLITSEARCH_IMPORT __declspec(dllimport)
#  define FABRICSERICES_SPLITSEARCH_EXPORT __declspec(dllexport)
# endif
#else
# if defined(SWIG)
#  define FABRICSERICES_SPLITSEARCH_IMPORT extern "C"
#  define FABRICSERICES_SPLITSEARCH_EXPORT extern "C"
# else
#  define FABRICSERICES_SPLITSEARCH_IMPORT extern "C" __attribute__ ((visibility("default")))
#  define FABRICSERICES_SPLITSEARCH_EXPORT extern "C" __attribute__ ((visibility("default")))
# endif
#endif

#if defined(FABRICSERICES_SPLITSEARCH_BUILDING)
# define FABRICSERICES_SPLITSEARCH_DECL FABRICSERICES_SPLITSEARCH_EXPORT
#else
# define FABRICSERICES_SPLITSEARCH_DECL FABRICSERICES_SPLITSEARCH_IMPORT
#endif

typedef void *FabricServices_SplitSearch_Dict;
typedef void *FabricServices_SplitSearch_Matches;

FABRICSERICES_SPLITSEARCH_DECL
FabricServices_SplitSearch_Dict FabricServices_SplitSearch_Dict_Create();

FABRICSERICES_SPLITSEARCH_DECL
bool FabricServices_SplitSearch_Dict_Add(
  FabricServices_SplitSearch_Dict dict,
  unsigned numCStrs,
  char const * const *cStrs,
  void *userdata
  );

FABRICSERICES_SPLITSEARCH_DECL
bool FabricServices_SplitSearch_Dict_Remove(
  FabricServices_SplitSearch_Dict dict,
  unsigned numCStrs,
  char const * const *cStrs,
  void *userdata
  );

FABRICSERICES_SPLITSEARCH_DECL
void FabricServices_SplitSearch_Dict_Clear(
  FabricServices_SplitSearch_Dict dict
  );

FABRICSERICES_SPLITSEARCH_DECL
FabricServices_SplitSearch_Matches FabricServices_SplitSearch_Dict_Search(
  FabricServices_SplitSearch_Dict _dict,
  char const *cStr
  );

FABRICSERICES_SPLITSEARCH_DECL
void FabricServices_SplitSearch_Matches_Destroy(
  FabricServices_SplitSearch_Matches _matches
  );

FABRICSERICES_SPLITSEARCH_DECL
void FabricServices_SplitSearch_Dict_Destroy(
  FabricServices_SplitSearch_Dict dict
  );

namespace FabricServices { namespace SplitSearch {

class Dict
{
private:

  // Deleted methods
  Dict( Dict const & );
  Dict &operator=( Dict const & );

public:

  Dict()
  {
    _dict = FabricServices_SplitSearch_Dict_Create();
  }

  ~Dict()
  {
    FabricServices_SplitSearch_Dict_Destroy( _dict );
  }

  bool add(
    unsigned numCStrs,
    char const * const *cStrs,
    void *userdata
    )
  {
    return FabricServices_SplitSearch_Dict_Add(
      _dict,
      numCStrs,
      cStrs,
      userdata
      );
  }

  bool remove(
    unsigned numCStrs,
    char const * const *cStrs,
    void *userdata
    )
  {
    return FabricServices_SplitSearch_Dict_Remove(
      _dict,
      numCStrs,
      cStrs,
      userdata
      );
  }

  void clear()
  {
    FabricServices_SplitSearch_Dict_Clear( _dict );
  }

private:

  FabricServices_SplitSearch_Dict _dict;
};


} }

#endif //_FABRIC_SplitSearch_hpp
