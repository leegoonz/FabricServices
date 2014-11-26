// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

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

      View(GraphExecutable graph);
      virtual ~View();

      bool isValid() const;

      GraphExecutable getGraph();

    protected:
      
      virtual void onNotification(char const * json) = 0;
      virtual void onNodeInserted(Node node) = 0;
      virtual void onNodeRemoved(Node node) = 0;
      virtual void onPinInserted(Pin pin) = 0;
      virtual void onPinRemoved(Pin pin) = 0;
      virtual void onPortInserted(Port port) = 0;
      virtual void onPortRemoved(Port port) = 0;
      virtual void onEndPointsConnected(Port src, Port dst) = 0;
      virtual void onEndPointsDisconnected(Port src, Port dst) = 0;
      virtual void onNodeMetadataChanged(Node node, const char * key, const char * metadata) = 0;
      virtual void onExecMetadataChanged(Executable exec, const char * key, const char * metadata) = 0;

    private:

      static void callback(void * userData, char const * jsonCString, uint32_t jsonLength);

      FabricCore::DFGView m_view;
      GraphExecutable m_graph;
    };

  };

};


#endif // __DFGWrapper_View__
