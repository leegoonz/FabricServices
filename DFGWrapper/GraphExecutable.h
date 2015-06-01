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

    class Inst;
    typedef FTL::SharedPtr<Inst> InstPtr;
    typedef std::vector<InstPtr> InstList;

    class GraphExecutable : public Executable
    {
      friend class Binding;
      friend class Node;
      friend class View;

    public:

      virtual bool isGraph() { return true; }

      static GraphExecutablePtr Create(
        FabricCore::DFGBinding const &dfgBinding,
        char const *execPath,
        FabricCore::DFGExec const &dfgExec
        )
      {
        return new GraphExecutable( dfgBinding, execPath, dfgExec );
      }

      virtual ~GraphExecutable()
      {
      }

      InstPtr addInstFromPreset(char const * preset);
      InstPtr addInstWithNewGraph(char const * title = 0);
      InstPtr addInstWithNewFunc(char const * title = 0);
      InstPtr addInstFromJSON(char const * json);

      NodeList getNodes();
      NodePtr getNode(char const * name);
      NodePtr getNode(uint32_t index);
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
        FabricCore::DFGBinding const &dfgBinding,
        char const *execPath,
        FabricCore::DFGExec const &dfgExec
        )
        : Executable( dfgBinding, execPath, dfgExec )
      {
      }

    };

  };

};


#endif // __DFGWrapper_GraphExecutable__
