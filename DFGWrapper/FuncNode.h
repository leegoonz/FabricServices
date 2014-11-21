// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __DFGWrapper_FuncNode__
#define __DFGWrapper_FuncNode__

#include <FabricCore.h>
#include "Node.h"

namespace FabricServices
{

  namespace DFGWrapper
  {

    class FuncNode : public Node
    {
      friend class GraphNode;

    public:

      FuncNode(const Node & other);
      FuncNode(const FuncNode & other);
      virtual ~FuncNode();

      // std::string getCode();
      // void setCode(char const *path, char const *code);

    protected:
      
      FuncNode(FabricCore::DFGBinding binding, std::string path);

    };

  };

};


#endif // __DFGWrapper_FuncNode__
