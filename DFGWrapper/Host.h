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

      void importJSON(char const * parentNameSpace, char const * json, char const * importPathname = 0);
      std::string exportJSON(char const * execPath);

      Binding createBindingToNewGraph();
      Binding createBindingFromJSON(char const * json, uint32_t rtValCount = 0, FabricCore::RTVal const *rtVals = 0);
      Binding createBindingToPreset(char const * preset, uint32_t rtValCount = 0, FabricCore::RTVal const *rtVals = 0);

    private:

      FabricCore::DFGHost m_host;      
    };

  };

};


#endif // __DFGWrapper_Host__
