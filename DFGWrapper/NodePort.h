// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __DFGWrapper_NodePort__
#define __DFGWrapper_NodePort__

#include <FabricCore.h>
#include <string>
#include <vector>

#include "Port.h"

namespace FabricServices
{

  namespace DFGWrapper
  {
    class Node;
    typedef FTL::SharedPtr<Node> NodePtr;
    typedef std::vector<NodePtr> NodeList;

    class ExecPort;
    typedef FTL::SharedPtr<ExecPort> ExecPortPtr;
    typedef std::vector<ExecPortPtr> ExecPortList;

    class NodePort;
    typedef FTL::SharedPtr<NodePort> NodePortPtr;
    typedef std::vector<NodePortPtr> NodePortList;
    
    class NodePort : public Port
    {
      friend class Node;
      friend class View;
      friend class Port;

    public:

      virtual bool isNodePort() const { return true; }

      static NodePortPtr Create(FabricCore::DFGBinding binding, FabricCore::DFGExec exec, char const * execPath, char const * nodePortPath);
      virtual ~NodePort();

      char const *getNodePortPath() const
        { return getPortPath(); }

      virtual std::string getDesc();
      virtual char const *getMetadata(char const * key) const;
      virtual void setMetadata(char const * key, char const * value, bool canUndo = false);

      virtual char const *getName() const
      {
        return FabricCore::DFGExec(getWrappedCoreExec()).getNodePortName(getNodePortPath());
      }
      virtual char const *getResolvedType() const
      {
        char const * result = FabricCore::DFGExec(getWrappedCoreExec()).getNodePortResolvedType(getNodePortPath());
        if(result)
          return result;
        return "";
      }

      void addDebugNodePort();
      FabricCore::RTVal getDebugNodePortValue();
      void removeDebugNodePort();

      virtual FabricCore::RTVal getDefaultValue( char const * dataType = NULL ) const;
      virtual void setDefaultValue( FabricCore::RTVal const &value );

      NodePtr getNode();
      ExecPortPtr getPort();

    protected:
      
      NodePort(FabricCore::DFGBinding binding, FabricCore::DFGExec exec, char const * execPath, char const * nodePortPath);

    };

  };

};


#endif // __DFGWrapper_NodePort__
