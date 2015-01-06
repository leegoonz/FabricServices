// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __DFGWrapper_Graph__
#define __DFGWrapper_Graph__

#include <FabricCore.h>
#include <string>
#include <vector>

#include "Object.h"

namespace FabricServices
{

  namespace DFGWrapper
  {

    class Graph : public Object
    {
      friend class NameSpace;

    public:

      Graph(const Graph & other);
      virtual ~Graph();

    protected:
      
      Graph(FabricCore::DFGHost host, std::string path);

    };

  };

};


#endif // __DFGWrapper_NameSpace__
