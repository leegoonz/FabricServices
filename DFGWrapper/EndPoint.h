// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __DFGWrapper_EndPoint__
#define __DFGWrapper_EndPoint__

#include "Element.h"

namespace FabricServices
{

  namespace DFGWrapper
  {

    class EndPoint : public Element
    {
    public:

      // Element - Type

      virtual bool isEndPoint() const { return true; }

      // EndPoint - Accessors

      char const *getEndPointPath() const
        { return m_endPointPath.c_str(); }

      FabricCore::DFGPortType getEndPointType() const
      {
        return getWrappedCoreBinding()->getEndPointType(
          getExecPath(), getEndPointPath()
          );
      }

      virtual char const *getDataType() const = 0;

      // EndPoint - Default Values

      virtual FabricCore::RTVal getDefaultValue( char const * dataType = NULL ) const = 0;
      virtual void setDefaultValue( FabricCore::RTVal const &value ) = 0;

      // EndPoint - Connections

      bool canConnect( SharedPtr<EndPoint const> const &dst ) const
      {
        getWrappedCoreBinding()->canConnect(
          getExecPath(), getEndPointPath(), dst->getEndPointPath()
          );
      }

      void connect( SharedPtr<EndPoint> const &dst )
      {
        getWrappedCoreBinding()->connect(
          getExecPath(), getEndPointPath(), dst->getEndPointPath()
          );
      }

      void disconnect( SharedPtr<EndPoint> const &dst )
      {
        getWrappedCoreBinding()->disconnect(
          getExecPath(), getEndPointPath(), dst->getEndPointPath()
          );
      }

      void disconnectAll()
      {
        getWrappedCoreBinding()->disconnectAll(
          getExecPath(), getEndPointPath()
          );
      }

      bool isConnected() const
      {
        return getWrappedCoreBinding()->isConnected(
          getExecPath(), getEndPointPath()
          );
      }

      SharedPtr<EndPoint> getSource() const;
      std::vector< SharedPtr<EndPoint> > getDestinations() const;

    protected:
      
      EndPoint(
        FabricCore::DFGBinding const &binding,
        char const *execPath,
        char const *endPointPath
        )
        : Element(
          binding,
          execPath
          )
        , m_endPointPath( endPointPath )
      {
      }

      static SharedPtr<EndPoint> Create(
        FabricCore::DFGBinding const &binding,
        char const *execPath,
        char const *endPointPath
        );

    private:

      std::string m_endPointPath;

    };

  };

};


#endif // __DFGWrapper_EndPoint__
