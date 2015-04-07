// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __DFGWrapper_View__
#define __DFGWrapper_View__

#include <FabricCore.h>
#include <string>
#include <vector>

#include "GraphExecutable.h"
#include "Node.h"
#include "Pin.h"

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
      virtual void onPinInserted(PinPtr pin) = 0;
      virtual void onPinRemoved(PinPtr pin) = 0;
      virtual void onPortInserted(PortPtr port) = 0;
      virtual void onPortRemoved(PortPtr port) = 0;
      virtual void onEndPointsConnected(EndPointPtr src, EndPointPtr dst) = 0;
      virtual void onEndPointsDisconnected(EndPointPtr src, EndPointPtr dst) = 0;
      virtual void onNodeMetadataChanged(NodePtr node, const char * key, const char * metadata) = 0;
      virtual void onNodeTitleChanged(NodePtr node, const char * title) = 0;
      virtual void onPortRenamed(PortPtr port, const char * oldName) = 0;
      virtual void onPinRenamed(PinPtr pin, const char * oldName) = 0;
      virtual void onExecMetadataChanged(ExecutablePtr exec, const char * key, const char * metadata) = 0;
      virtual void onExtDepAdded(const char * extension, const char * version) = 0;
      virtual void onExtDepRemoved(const char * extension, const char * version) = 0;
      virtual void onNodeCacheRuleChanged(const char * path, const char * rule) = 0;
      virtual void onExecCacheRuleChanged(const char * path, const char * rule) = 0;
      virtual void onPortResolvedTypeChanged(PortPtr port, const char * resolvedType) = 0;
      virtual void onPinResolvedTypeChanged(PinPtr pin, const char * resolvedType) = 0;

    private:

      static void callback(void * userData, char const * jsonCString, uint32_t jsonLength);

      FabricCore::DFGView m_view;
      GraphExecutablePtr m_graph;
    };

  };

};


#endif // __DFGWrapper_View__
