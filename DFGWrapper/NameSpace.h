// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __DFGWrapper_NameSpace__
#define __DFGWrapper_NameSpace__

#include <FabricCore.h>
#include <string>
#include <vector>

#include "Object.h"
#include "Func.h"
#include "Graph.h"

namespace FabricServices
{

  namespace DFGWrapper
  {

    class NameSpace : public Object
    {
      friend class Host;

    public:

      NameSpace(const NameSpace & other);
      virtual ~NameSpace();

      std::vector<NameSpace> getNameSpaces(bool recursive = false);
      std::vector<Func> getFuncs(bool recursive = false);
      std::vector<Graph> getGraphs(bool recursive = false);

      NameSpace addNameSpace(char const *displayName);

    protected:
      
      NameSpace(FabricCore::DFGHost host, std::string path);

    };

  };

};


#endif // __DFGWrapper_NameSpace__
