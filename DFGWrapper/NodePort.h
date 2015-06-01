// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __DFGWrapper_NodePort__
#define __DFGWrapper_NodePort__

#include "Port.h"

namespace FabricServices
{

  namespace DFGWrapper
  {

    class Node;
    typedef FTL::SharedPtr<Node> NodePtr;
    typedef std::vector<NodePtr> NodeList;

    class NodePort;
    typedef FTL::SharedPtr<NodePort> NodePortPtr;
    typedef std::vector<NodePortPtr> NodePortList;
    
    class NodePort : public Port
    {

    public:

      virtual bool isNodePort() { return true; }

      static NodePortPtr Create(
        FabricCore::DFGBinding const &dfgBinding,
        char const *execPath,
        FabricCore::DFGExec const &dfgExec,
        char const *nodeName,
        char const *portName
        );

      static NodePortPtr Create(
        FabricCore::DFGBinding const &dfgBinding,
        char const *execPath,
        FabricCore::DFGExec const &dfgExec,
        char const *portPath
        );

      virtual ~NodePort()
      {
      }

      virtual char const *getPortName()
        { return m_portName.c_str(); }

      char const *getNodeName()
        { return m_nodeName.c_str(); }

      virtual std::string getDesc()
      {
        return getDFGExec().getNodePortDesc(getPortPath()).getCString();
      }

      virtual char const *getMetadata(char const * key)
      {
        return getDFGExec().getNodePortMetadata(getPortPath(), key);
      }

      virtual void setMetadata(
        char const * key,
        char const * value,
        bool canUndo = false
        )
      {
        getDFGExec().setNodePortMetadata(getPortPath(), key, value, canUndo);
      }

      virtual char const *getResolvedType()
      {
        char const * result =
          getDFGExec().getNodePortResolvedType(getPortPath());
        return result? result: "";
      }

      NodePtr getNode();

    protected:
      
      NodePort(
        FabricCore::DFGBinding const &dfgBinding,
        char const *execPath,
        FabricCore::DFGExec const &dfgExec,
        char const *nodeName,
        char const *portName
        )
        : Port(
          dfgBinding,
          execPath,
          dfgExec,
          nodeName,
          portName
          )
        , m_nodeName(nodeName)
        , m_portName(portName)
      {
      }

      NodePort(
        FabricCore::DFGBinding const &dfgBinding,
        char const *execPath,
        FabricCore::DFGExec const &dfgExec,
        char const *portPath
        )
        : Port(
          dfgBinding,
          execPath,
          dfgExec,
          portPath
          )
      {
        char const *dot = strchr( portPath, '.' );
        unsigned nodeSize = dot - portPath;
        m_nodeName = std::string( portPath, nodeSize );
        m_portName = dot + 1;
      }

    private:

      std::string m_nodeName;
      std::string m_portName;

    };

  };

};


#endif // __DFGWrapper_NodePort__
