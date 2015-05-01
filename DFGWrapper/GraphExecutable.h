// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __DFGWrapper_GraphExecutable__
#define __DFGWrapper_GraphExecutable__

#include <FabricCore.h>
#include "Executable.h"
#include "Node.h"
#include "Connection.h"

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

      NodeList getNodes();
      NodePtr getNode(char const * name);
      void removeNode(NodePtr node);

      std::string exportNodesJSON(uint32_t nodeCount, char const * const *nodeNames);
      std::string importNodesJSON(char const *nodesJSON);
      char const * implodeNodes(char const *desiredName, uint32_t nodeCount, char const * const *nodeNames);
      std::vector<std::string> explodeNode(char const * nodeName);

      ConnectionList getConnections();

      bool canConnectTo(
        char const *srcPath,
        char const *dstPath,
        std::string &failureReason
      );

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
