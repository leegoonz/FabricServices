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
    class ExecPort : public Port
    {
      friend class Executable;
      friend class View;
      friend class Port;

    public:

      virtual bool isExecPort() const { return true; }

      static ExecPortPtr Create(FabricCore::DFGBinding binding, FabricCore::DFGExec exec, char const * execPath, char const * portPath);

      virtual ~ExecPort();

      char const *getExecPortPath() const
        { return getPortPath(); }

      FabricCore::DFGPortType getOutsidePortType() const
      {
        return FabricCore::DFGExec(getWrappedCoreExec()).getExecPortOutsidePortType(
          getExecPortPath()
        );
      }

      void setOutsidePortType(FabricCore::DFGPortType type)
      {
        FabricCore::DFGExec(getWrappedCoreExec()).setExecPortOutsidePortType(getExecPortPath(), type);
      }

      virtual std::string getDesc();
      virtual char const *getMetadata(char const * key) const;
      virtual void setMetadata(char const * key, char const * value, bool canUndo = false);

      virtual char const *getName() const
      {
        return FabricCore::DFGExec( m_exec ).getExecPortName( getExecPortPath() );
      }

      virtual char const *getResolvedType() const
      {
        char const * result = FabricCore::DFGExec(m_exec).getExecPortResolvedType(getExecPortPath());
        if(result)
          return result;
        return "";
      }

      virtual char const *getTypeSpec() const
      {
        char const * result = FabricCore::DFGExec(m_exec).getExecPortTypeSpec(getExecPortPath());
        if(result)
          return result;
        return "";
      }

      virtual void setTypeSpec(char const * spec)
      {
        m_exec.setExecPortTypeSpec(getExecPortPath(), spec);
      }

      virtual char const *rename(char const * name);

      virtual FabricCore::RTVal getDefaultValue( char const * dataType = NULL ) const;
      virtual void setDefaultValue( FabricCore::RTVal const &value );

      virtual FabricCore::RTVal getArgValue();
      virtual void setArgValue( FabricCore::RTVal const &value );

    protected:
      
      ExecPort(FabricCore::DFGBinding binding, FabricCore::DFGExec exec, char const * execPath, char const * portPath);

    };

  };

};


#endif // __DFGWrapper_ExecPort__
