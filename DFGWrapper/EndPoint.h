// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __DFGWrapper_EndPoint__
#define __DFGWrapper_EndPoint__

#include <vector>
#include "Element.h"

namespace FabricServices
{

  namespace DFGWrapper
  {
    class EndPoint;
    typedef FTL::SharedPtr<EndPoint> EndPointPtr;
    typedef std::vector<EndPointPtr> EndPointList;

    class EndPoint : public Element
    {
    public:

      static EndPointPtr Create(
        FabricCore::DFGBinding const &binding,
        FabricCore::DFGExec const &exec,
        char const *execPath,
        char const *endPointPath
        );

      // Element - Type

      virtual bool isEndPoint() const { return true; }

      // EndPoint - Accessors

      char const *getEndPointPath() const
        { return m_endPointPath.c_str(); }

      FabricCore::DFGPortType getEndPointType() const
      {
        return FabricCore::DFGExec(getWrappedCoreExec()).getEndPointType(
          getEndPointPath()
        );
      }

      virtual char const *getName() const = 0;
      virtual char const *getResolvedType() const = 0;

      // EndPoint - Default Values

      virtual FabricCore::RTVal getDefaultValue( char const * dataType = NULL ) const = 0;
      virtual void setDefaultValue( FabricCore::RTVal const &value ) = 0;

      // EndPoint - Connections

      bool canConnectTo( EndPointPtr dst ) const
      {
        return getWrappedCoreExec().canConnectTo(
          getEndPointPath(), dst->getEndPointPath()
          );
      }

      void connectTo( EndPointPtr dst )
      {
        getWrappedCoreExec().connectTo(
          getEndPointPath(), dst->getEndPointPath()
        );
      }

      void disconnectFrom( EndPointPtr dst )
      {
        getWrappedCoreExec().disconnectFrom(
          getEndPointPath(), dst->getEndPointPath()
        );
      }

      void disconnectFromAll()
      {
        getWrappedCoreExec().disconnectFromAll(
          getEndPointPath()
        );
      }

      bool isConnectedToAny() const
      {
        return getWrappedCoreExec().isConnectedToAny(getEndPointPath());
      }

    protected:
      
      EndPoint(
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

      EndPoint(EndPoint const & other)
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


#endif // __DFGWrapper_EndPoint__
