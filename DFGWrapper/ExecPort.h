// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __DFGWrapper_ExecPort__
#define __DFGWrapper_ExecPort__

#include <FabricCore.h>
#include <string>
#include <vector>

#include "NodePort.h"

namespace FabricServices
{

  namespace DFGWrapper
  {

    class ExecPort;
    typedef FTL::SharedPtr<ExecPort> ExecPortPtr;
    typedef std::vector<ExecPortPtr> ExecPortList;

    class ExecPort : public Port
    {

    public:

      virtual bool isExecPort() { return true; }

      static ExecPortPtr Create(
        FabricCore::DFGBinding dfgBinding,
        char const *execPath,
        FabricCore::DFGExec dfgExec, 
        char const *portName
        )
      {
        return new ExecPort(dfgBinding, execPath, dfgExec, portName);
      }

      virtual ~ExecPort()
      {
      }

      FabricCore::DFGPortType getExecPortType()
      {
        return getDFGExec().getExecPortType( getPortPath() );
      }

      void setExecPortType(FabricCore::DFGPortType type)
      {
        getDFGExec().setExecPortType(getPortPath(), type);
      }

      virtual std::string getDesc()
      {
        return getDFGExec().getExecPortDesc(getPortPath()).getCString();
      }

      virtual char const *getMetadata(char const * key)
      {
        return getDFGExec().getExecPortMetadata(getPortPath(), key);
      }

      virtual void setMetadata(
        char const * key,
        char const * value,
        bool canUndo = false
        )
      {
        getDFGExec().setExecPortMetadata(getPortPath(), key, value, canUndo);
      }

      virtual char const *getPortName()
      {
        return getPortPath();
      }

      virtual char const *getResolvedType()
      {
        char const * result =
          getDFGExec().getExecPortResolvedType(getPortPath());
        return result? result: "";
      }

      virtual char const *getTypeSpec()
      {
        char const * result =
          getDFGExec().getExecPortTypeSpec(getPortPath());
        return result? result: "";
      }

      virtual void setTypeSpec(char const * spec)
      {
        getDFGExec().setExecPortTypeSpec(getPortPath(), spec);
      }

      char const *rename(char const * desiredName)
      {
        char const *actualNameCStr =
          getDFGExec().renameExecPort(getPortPath(), desiredName);
        updateElementPath( actualNameCStr );
        return actualNameCStr;
      }

      virtual FabricCore::RTVal getArgValue()
      {
        return getDFGBinding().getArgValue(getPortPath());
      }

      virtual void setArgValue( FabricCore::RTVal const &value )
      {
        getDFGBinding().setArgValue(getPortPath(), value);
      }

    protected:
      
      ExecPort(
        FabricCore::DFGBinding dfgBinding,
        char const *execPath,
        FabricCore::DFGExec dfgExec,
        char const *portName
        )
        : Port(dfgBinding, execPath, dfgExec, portName)
      {
      }

    };

  };

};


#endif // __DFGWrapper_ExecPort__
