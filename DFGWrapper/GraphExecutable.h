// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __DFGWrapper_GraphExecutable__
#define __DFGWrapper_GraphExecutable__

#include <FabricCore.h>
#include "Executable.h"
#include "Node.h"
// #include "Connection.h"

namespace FabricServices
{

  namespace DFGWrapper
  {

    class GraphExecutable : public Executable
    {
      friend class Binding;
      friend class Node;
      friend class View;

    public:

      GraphExecutable(const Executable & other);
      GraphExecutable(const GraphExecutable & other);
      virtual ~GraphExecutable();

      char const *getGraphPath() const { return getExecPath(); }

      Node addNodeFromPreset(char const * preset);
      Node addNodeWithNewGraph(char const * title = 0);
      Node addNodeWithNewFunc(char const * title = 0);
      Node addNodeFromJSON(char const * json);

      std::vector<Node> getNodes();
      Node getNode(char const * name);
      void removeNode(Node node);

      // todo
      // std::vector<Connection> getConnections();

    protected:
      
      GraphExecutable();
      GraphExecutable(
        FabricCore::DFGBinding binding,
        FabricCore::DFGExec exec,
        const char * graphPath
      );

    };

  };

};


#endif // __DFGWrapper_GraphExecutable__
