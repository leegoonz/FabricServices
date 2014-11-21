// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __DFGWrapper_Host__
#define __DFGWrapper_Host__

#include <FabricCore.h>

#include "NameSpace.h"
#include "Binding.h"

namespace FabricServices
{

  namespace DFGWrapper
  {

    class Host
    {

    public:

      Host(FabricCore::Client client);
      Host(const Host & other);

      virtual ~Host();

      FabricCore::DFGHost getWrappedCoreHost() const;

      bool maybeUndo();
      bool maybeRedo();

      NameSpace getRootNameSpace() const;

      // this should be a simple call without parent namespace, additional namespaces should be built as children
      // DFGStringResult addNamespace(char const *parentNameSpace, char const *displayName);

      // todo once we have a namespace wrapper
      //DFGStringResult importJSON(char const *parentNameSpace, char const *json, char const *importPathname = 0);
      //DFGStringResult exportJSON(char const *execPath);

      // construct a new binding
      //DFGBinding createBindingToNewGraph()

      // todo: what do these do exactly
      // DFGBinding createBindingFromJSON(char const *json, uint32_t rtValCount = 0, RTVal const *rtVals = 0);
      // DFGBinding createBindingToPreset(char const *execPath, uint32_t rtValCount = 0, RTVal const *rtVals = 0);

    private:

      FabricCore::DFGHost m_host;      
    };

  };

};


#endif // __DFGWrapper_Host__
