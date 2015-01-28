// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __DFGWrapper_GraphExecutable__
#define __DFGWrapper_GraphExecutable__

#include <FabricCore.h>
#include "Executable.h"
#include "Connection.h"
#include "Node.h"

namespace FabricServices
{

  namespace DFGWrapper
  {

    class GraphExecutable : public Executable
    {
      friend class Binding;
      friend class Node;

    public:

      GraphExecutable(const Executable & other);
      GraphExecutable(const GraphExecutable & other);
      virtual ~GraphExecutable();

      Node addNodeFromPreset(char const * preset);
      Node addNodeWithNewGraph(char const * title = 0);
      Node addNodeWithNewFunc(char const * title = 0);
      Node addNodeFromJSON(char const * json);

      std::vector<Node> getNodes();
      Node getNode(char const * name);
      void removeNode(Node node);


      std::vector<Connection> getConnections();

    protected:
      
      GraphExecutable(FabricCore::DFGBinding binding, std::string path);

    };

  };

};


#endif // __DFGWrapper_GraphExecutable__
