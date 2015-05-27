// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __DFGWrapper_Port__
#define __DFGWrapper_Port__

#include <vector>
#include "Element.h"

namespace FabricServices
{

  namespace DFGWrapper
  {
    class Port;
    typedef FTL::SharedPtr<Port> PortPtr;
    typedef std::vector<PortPtr> PortList;

    class Port : public Element
    {
    public:

      static PortPtr Create(
        FabricCore::DFGBinding const &binding,
        FabricCore::DFGExec const &exec,
        char const *execPath,
        char const *endPointPath
        );

      // Element - Type

      virtual bool isPort() const { return true; }

      // Port - Accessors

      char const *getPortPath() const
        { return m_endPointPath.c_str(); }

      FabricCore::DFGPortType getInsidePortType() const
      {
        return FabricCore::DFGExec(getWrappedCoreExec()).getInsidePortType(
          getPortPath()
        );
      }

      virtual char const *getName() const = 0;
      virtual char const *getResolvedType() const = 0;

      // Port - Default Values

      virtual FabricCore::RTVal getDefaultValue( char const * dataType = NULL ) const = 0;
      virtual void setDefaultValue( FabricCore::RTVal const &value ) = 0;

      // Port - Connections

      bool canConnectTo( PortPtr dst ) const
      {
        return getWrappedCoreExec().canConnectTo(
          getPortPath(), dst->getPortPath()
          );
      }

      void connectTo( PortPtr dst )
      {
        getWrappedCoreExec().connectTo(
          getPortPath(), dst->getPortPath()
        );
      }

      void disconnectFrom( PortPtr dst )
      {
        getWrappedCoreExec().disconnectFrom(
          getPortPath(), dst->getPortPath()
        );
      }

      void disconnectFromAll()
      {
        getWrappedCoreExec().disconnectFromAll(
          getPortPath()
        );
      }

      bool isConnectedToAny() const
      {
        return getWrappedCoreExec().isConnectedToAny(getPortPath());
      }

    protected:
      
      Port(
        FabricCore::DFGBinding const &binding,
        FabricCore::DFGExec const &exec,
        char const *execPath,
        char const *endPointPath
        )
        : Element(
          binding,
          exec,
          execPath
          )
        , m_endPointPath( endPointPath )
      {
      }

      Port(Port const & other)
        : Element(
          other.m_binding,
          other.m_exec,
          other.getElementPath()
          )
        , m_endPointPath( other.m_endPointPath )
      {
      }

    private:

      mutable std::string m_name;
      std::string m_endPointPath;

    };

  };

};


#endif // __DFGWrapper_Port__
