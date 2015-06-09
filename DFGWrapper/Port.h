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
        char const *execPath,
        FabricCore::DFGExec const &exec,
        char const *portPath
        );

      // Element - Type

      virtual bool isPort() { return true; }

      // Port - Accessors

      char const *getPortPath()
        { return getElementPath(); }

      virtual char const *getPortName() = 0;

      FabricCore::DFGPortType getNodePortType()
      {
        return getDFGExec().getNodePortType( getElementPath() );
      }

      virtual char const *getResolvedType() = 0;

      // Port - Connections

      bool canConnectTo( PortPtr dst )
      {
        return getDFGExec().canConnectTo(
          getElementPath(), dst->getElementPath()
          );
      }

      void connectTo( PortPtr dst )
      {
        getDFGExec().connectTo(
          getElementPath(), dst->getElementPath()
        );
      }

      void disconnectFrom( PortPtr dst )
      {
        getDFGExec().disconnectFrom(
          getElementPath(), dst->getElementPath()
        );
      }

      void disconnectFromAll()
      {
        getDFGExec().disconnectFromAll( getElementPath() );
      }

      bool isConnectedToAny()
      {
        return getDFGExec().isConnectedToAny( getElementPath() );
      }

      // Port - defaultValues

      virtual FabricCore::RTVal getDefaultValue( char const * dataType )
      {
        return getDFGExec().getPortDefaultValue(getPortPath(), dataType);
      }

      virtual void setDefaultValue( FabricCore::RTVal const &value )
      {
        getDFGExec().setPortDefaultValue(getPortPath(), value);
      }

    protected:
      
      Port(
        FabricCore::DFGBinding const &dfgBinding,
        char const *execPath,
        FabricCore::DFGExec const &dfgExec,
        char const *portPath
        )
        : Element(
          dfgBinding,
          execPath,
          dfgExec,
          portPath
          )
      {
      }
      
      Port(
        FabricCore::DFGBinding const &dfgBinding,
        char const *execPath,
        FabricCore::DFGExec const &dfgExec,
        char const *nodeName,
        char const *portName
        )
        : Element(
          dfgBinding,
          execPath,
          dfgExec,
          nodeName,
          portName
          )
      {
      }

    };

  };

};

#endif // __DFGWrapper_Port__
