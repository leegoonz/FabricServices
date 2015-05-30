// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __DFGWrapper_Inst__
#define __DFGWrapper_Inst__

#include <FabricCore.h>
#include <string>
#include <vector>
#include "Node.h"
#include "NodePort.h"

namespace FabricServices
{

  namespace DFGWrapper
  {

    class InstPort;
    typedef FTL::SharedPtr<InstPort> InstPortPtr;
    typedef std::vector<InstPortPtr> InstPortList;

    class Inst;
    typedef FTL::SharedPtr<Inst> InstPtr;
    typedef std::vector<InstPtr> InstList;

    class Inst : public Node
    {
    public:

      virtual bool isInst() { return true; }

      static InstPtr Create(
        FabricCore::DFGBinding const &dfgBinding,
        char const *execPath,
        FabricCore::DFGExec const &dfgExec,
        char const *instName
        )
      {
        return new Inst(
          dfgBinding,
          execPath,
          dfgExec,
          instName
          );
      }

      virtual ~Inst()
      {
      }

      char const *getInstPath()
        { return getNodePath(); }

      char const *getInstName()
        { return getNodeName(); }

      ExecutablePtr getExecutable()
      {
        std::string subExecPath = getExecPath();
        if ( !subExecPath.empty() )
          subExecPath += '.';
        subExecPath += getInstPath();
        return Executable::Create(
          getDFGBinding(),
          subExecPath.c_str(),
          getDFGExec().getSubExec( getInstPath() )
          );
      }

      char const* getTitle()
      {
        return getDFGExec().getInstTitle( getInstPath() );
      }

      void setTitle(char const *title)
      {
        getDFGExec().setInstTitle(getInstPath(), title);
      }

      FEC_DFGCacheRule getCacheRule()
      {
        return getDFGExec().getInstCacheRule(getInstPath());
      }

      void setCacheRule(FEC_DFGCacheRule rule)
      {
        getDFGExec().setInstCacheRule(getInstPath(), rule);
      }

    protected:
      
      Inst(
        FabricCore::DFGBinding const &dfgBinding,
        char const *execPath,
        FabricCore::DFGExec const &dfgExec,
        char const *instName
        )
        : Node(
          dfgBinding,
          execPath,
          dfgExec,
          instName
          )
      {
      }

    };

  };

};


#endif // __DFGWrapper_Inst__
