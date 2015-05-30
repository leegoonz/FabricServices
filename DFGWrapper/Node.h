// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __DFGWrapper_Node__
#define __DFGWrapper_Node__

#include <FabricCore.h>
#include <string>
#include <vector>
#include "Executable.h"
#include "NodePort.h"

namespace FabricServices
{

  namespace DFGWrapper
  {

    class GraphExecutable;
    typedef FTL::SharedPtr<GraphExecutable> GraphExecutablePtr;

    class Node : public Element
    {

    public:

      virtual bool isNode() { return true; }

      static NodePtr Create(
        FabricCore::DFGBinding const &dfgBinding,
        char const *execPath,
        FabricCore::DFGExec const &dfgExec,
        char const *nodeName
        );

      virtual ~Node()
      {
      }

      char const *getNodePath()
        { return getElementPath(); }

      char const *getNodeName()
        { return getNodePath(); }

      GraphExecutablePtr getOwningGraphExecutable();

      virtual std::string getDesc()
      {
        return getDFGExec().getNodeDesc( getNodePath() ).getCString();
      }

      virtual char const *getMetadata(char const * key)
      {
        return getDFGExec().getNodeMetadata( getNodePath(), key );
      }

      virtual void setMetadata(char const * key, char const * metadata, bool canUndo)
      {
        return getDFGExec().setNodeMetadata(getNodePath(), key, metadata, canUndo);
      }

      NodePortList getNodePorts();
      NodePortPtr getNodePort(char const * portName);
      NodePortPtr getNodePort(uint32_t index);

    protected:
      
      Node(
        FabricCore::DFGBinding const &dfgBinding,
        char const *execPath,
        FabricCore::DFGExec const &dfgExec,
        char const *nodeName
        )
        : Element(
          dfgBinding,
          execPath,
          dfgExec,
          nodeName
          )
      {
      }

    };

  };

};


#endif // __DFGWrapper_Node__
