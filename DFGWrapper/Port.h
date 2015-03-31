// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __DFGWrapper_Port__
#define __DFGWrapper_Port__

#include <FabricCore.h>
#include <string>
#include <vector>

#include "EndPoint.h"

namespace FabricServices
{

  namespace DFGWrapper
  {
    class Port;
    typedef FTL::SharedPtr<Port> PortPtr;
    typedef std::vector<PortPtr> PortList;

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

      virtual std::string getDesc();
      virtual char const *getMetadata(char const * key) const;
      virtual void setMetadata(char const * key, char const * value, bool canUndo = false);

      virtual char const *getName() const
      {
        return FabricCore::DFGExec( m_exec ).getPortName( getPortPath() );
      }

      virtual char const *getResolvedType() const
      {
        return FabricCore::DFGExec( m_exec ).getPortResolvedType( getPortPath() );
      }

      char const *getTypeSpec() const
      {
        return FabricCore::DFGExec( m_exec ).getPortTypeSpec( getPortPath() );
      }

      virtual char const *rename(char const * name);

      virtual FabricCore::RTVal getDefaultValue( char const * dataType = NULL ) const;
      virtual void setDefaultValue( FabricCore::RTVal const &value );

    protected:
      
      Port(FabricCore::DFGBinding binding, FabricCore::DFGExec exec, char const * execPath, char const * portPath);

    };

  };

};


#endif // __DFGWrapper_Port__
