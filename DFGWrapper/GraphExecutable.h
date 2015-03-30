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
    class GraphExecutable;
    typedef FTL::SharedPtr<GraphExecutable> GraphExecutablePtr;

    class GraphExecutable : public Executable
    {
      friend class Binding;
      friend class Node;
      friend class View;

    public:

      virtual bool isGraph() const { return true; }

      static GraphExecutablePtr Create(
        FabricCore::DFGBinding binding,
        FabricCore::DFGExec exec,
        const char * graphPath
      );
      virtual ~GraphExecutable();

      char const *getGraphPath() const { return getExecPath(); }

      NodePtr addNodeFromPreset(char const * preset);
      NodePtr addNodeWithNewGraph(char const * title = 0);
      NodePtr addNodeWithNewFunc(char const * title = 0);
      NodePtr addNodeFromJSON(char const * json);

      std::vector<NodePtr> getNodes();
      NodePtr getNode(char const * name);
      void removeNode(Node node);

      // todo
      // std::vector<Connection> getConnections();

    protected:
      
      GraphExecutable(
        FabricCore::DFGBinding binding,
        FabricCore::DFGExec exec,
        const char * graphPath
      );

    };

  };

};


#endif // __DFGWrapper_GraphExecutable__
