// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __DFGWrapper_View__
#define __DFGWrapper_View__

#include <FabricCore.h>
#include <string>
#include <vector>

#include "GraphExecutable.h"
#include "Node.h"
#include "NodePort.h"

namespace FabricServices
{

  namespace DFGWrapper
  {

    class View
    {

      friend class GraphExecutable;

    public:

      View();
      View(GraphExecutablePtr graph);
      virtual ~View() {}

      bool isValid() const;

      void setGraph(GraphExecutablePtr graph);
      GraphExecutablePtr getGraph();

    protected:
      
      virtual void onNotification(char const * json) = 0;
      virtual void onNodeInserted(NodePtr node) = 0;
      virtual void onNodeRemoved(NodePtr node) = 0;
      virtual void onNodePortInserted(NodePortPtr nodePort) = 0;
      virtual void onNodePortRemoved(NodePortPtr nodePort) = 0;
      virtual void onExecPortInserted(ExecPortPtr port) = 0;
      virtual void onExecPortRemoved(ExecPortPtr port) = 0;
      virtual void onPortsConnected(PortPtr src, PortPtr dst) = 0;
      virtual void onPortsDisconnected(PortPtr src, PortPtr dst) = 0;
      virtual void onNodeMetadataChanged(NodePtr node, const char * key, const char * metadata) = 0;
      virtual void onNodeTitleChanged(NodePtr node, const char * title) = 0;
      virtual void onExecPortRenamed(ExecPortPtr port, const char * oldName) = 0;
      virtual void onNodePortRenamed(NodePortPtr nodePort, const char * oldName) = 0;
      virtual void onExecMetadataChanged(ExecutablePtr exec, const char * key, const char * metadata) = 0;
      virtual void onExtDepAdded(const char * extension, const char * version) = 0;
      virtual void onExtDepRemoved(const char * extension, const char * version) = 0;
      virtual void onNodeCacheRuleChanged(const char * path, const char * rule) = 0;
      virtual void onExecCacheRuleChanged(const char * path, const char * rule) = 0;
      virtual void onExecPortResolvedTypeChanged(ExecPortPtr port, const char * resolvedType) = 0;
      virtual void onExecPortTypeSpecChanged(ExecPortPtr port, const char * typeSpec) = 0;
      virtual void onNodePortResolvedTypeChanged(NodePortPtr nodePort, const char * resolvedType) = 0;
      virtual void onExecPortMetadataChanged(FabricServices::DFGWrapper::ExecPortPtr port, const char * key, const char * metadata) = 0;
      virtual void onNodePortMetadataChanged(FabricServices::DFGWrapper::NodePortPtr nodePort, const char * key, const char * metadata) = 0;
      virtual void onNodePortTypeChanged(NodePortPtr nodePort, FabricCore::DFGPortType nodePortType) = 0;
      virtual void onExecPortTypeChanged(ExecPortPtr port, FabricCore::DFGPortType portType) = 0;

    private:

      static void callback(void * userData, char const * jsonCString, uint32_t jsonLength);

      FabricCore::DFGView m_view;
      GraphExecutablePtr m_graph;
    };

  };

};


#endif // __DFGWrapper_View__
