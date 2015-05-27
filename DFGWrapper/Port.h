// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __DFGWrapper_Port__
#define __DFGWrapper_Port__

#include <FabricCore.h>
#include <string>
#include <vector>

#include "Pin.h"

namespace FabricServices
{

  namespace DFGWrapper
  {
    class Port : public EndPoint
    {
      friend class Executable;
      friend class View;
      friend class EndPoint;

    public:

      virtual bool isPort() const { return true; }

      static PortPtr Create(FabricCore::DFGBinding binding, FabricCore::DFGExec exec, char const * execPath, char const * portPath);

      virtual ~Port();

      char const *getPortPath() const
        { return getEndPointPath(); }

      FabricCore::DFGPortType getOutsidePortType() const
      {
        return FabricCore::DFGExec(getWrappedCoreExec()).getExecPortOutsidePortType(
          getPortPath()
        );
      }

      void setOutsidePortType(FabricCore::DFGPortType type)
      {
        FabricCore::DFGExec(getWrappedCoreExec()).setExecPortOutsidePortType(getPortPath(), type);
      }

      virtual std::string getDesc();
      virtual char const *getMetadata(char const * key) const;
      virtual void setMetadata(char const * key, char const * value, bool canUndo = false);

      virtual char const *getName() const
      {
        return FabricCore::DFGExec( m_exec ).getExecPortName( getPortPath() );
      }

      virtual char const *getResolvedType() const
      {
        char const * result = FabricCore::DFGExec(m_exec).getExecPortResolvedType(getPortPath());
        if(result)
          return result;
        return "";
      }

      virtual char const *getTypeSpec() const
      {
        char const * result = FabricCore::DFGExec(m_exec).getExecPortTypeSpec(getPortPath());
        if(result)
          return result;
        return "";
      }

      virtual void setTypeSpec(char const * spec)
      {
        m_exec.setExecPortTypeSpec(getPortPath(), spec);
      }

      virtual char const *rename(char const * name);

      virtual FabricCore::RTVal getDefaultValue( char const * dataType = NULL ) const;
      virtual void setDefaultValue( FabricCore::RTVal const &value );

      virtual FabricCore::RTVal getArgValue();
      virtual void setArgValue( FabricCore::RTVal const &value );

    protected:
      
      Port(FabricCore::DFGBinding binding, FabricCore::DFGExec exec, char const * execPath, char const * portPath);

    };

  };

};


#endif // __DFGWrapper_Port__
