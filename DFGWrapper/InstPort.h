// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __DFGWrapper_InstPort__
#define __DFGWrapper_InstPort__

#include "NodePort.h"

namespace FabricServices
{

  namespace DFGWrapper
  {
    class ExecPort;
    typedef FTL::SharedPtr<ExecPort> ExecPortPtr;
    typedef std::vector<ExecPortPtr> ExecPortList;

    class Inst;
    typedef FTL::SharedPtr<Inst> InstPtr;
    typedef std::vector<InstPtr> InstList;

    class InstPort;
    typedef FTL::SharedPtr<InstPort> InstPortPtr;
    typedef std::vector<InstPortPtr> InstPortList;
    
    class InstPort : public NodePort
    {

    public:

      virtual bool isInstPort() { return true; }

      static InstPortPtr Create(
        FabricCore::DFGBinding const &dfgBinding,
        char const *execPath,
        FabricCore::DFGExec const &dfgExec,
        char const *nodeName,
        char const *portName
        )
      {
        return new InstPort(
          dfgBinding,
          execPath,
          dfgExec,
          nodeName,
          portName
          );
      }

      static InstPortPtr Create(
        FabricCore::DFGBinding const &dfgBinding,
        char const *execPath,
        FabricCore::DFGExec const &dfgExec,
        char const *portPath
        )
      {
        return new InstPort(
          dfgBinding,
          execPath,
          dfgExec,
          portPath
          );
      }

      virtual ~InstPort()
      {
      }

      InstPtr getInst();

      ExecPortPtr getExecPort();

    protected:
      
      InstPort(
        FabricCore::DFGBinding const &dfgBinding,
        char const *execPath,
        FabricCore::DFGExec const &dfgExec,
        char const *nodeName,
        char const *portName
        )
        : NodePort(
          dfgBinding,
          execPath,
          dfgExec,
          nodeName,
          portName
          )
        {}

      InstPort(
        FabricCore::DFGBinding const &dfgBinding,
        char const *execPath,
        FabricCore::DFGExec const &dfgExec,
        char const *portPath
        )
        : NodePort(
          dfgBinding,
          execPath,
          dfgExec,
          portPath
          )
        {}

    };

  };

};


#endif // __DFGWrapper_InstPort__
