// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __DFGWrapper_GraphNode__
#define __DFGWrapper_GraphNode__

#include <FabricCore.h>
#include "Node.h"

namespace FabricServices
{

  namespace DFGWrapper
  {

    class GraphNode : public Node
    {
      friend class Binding;

    public:

      GraphNode(const GraphNode & other);
      virtual ~GraphNode();

      // graph node
      // DFGStringResult addNodeFromPreset(char const *parentGraphPath, char const *execPath);
      // DFGStringResult addNodeWithNewGraph(char const *parentGraphPath, char const *title = 0);
      // DFGStringResult addNodeWithNewFunc(char const *parentGraphPath, char const *title = 0);
      // DFGStringResult addNodeFromJSON(char const *parentGraphPath, char const *json);

    protected:
      
      GraphNode(FabricCore::DFGBinding binding, std::string path);

    };

  };

};


#endif // __DFGWrapper_GraphNode__
