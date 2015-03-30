// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __DFGWrapper_EndPoint__
#define __DFGWrapper_EndPoint__

#include "Element.h"

namespace FabricServices
{

  namespace DFGWrapper
  {
    class EndPoint;
    typedef FTL::SharedPtr<EndPoint> EndPointPtr;

    class EndPoint : public FTL::Shareable, public Element
    {
    public:

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

      virtual char const *getName() const
      {
        if(m_name.length() == 0)
        {
          m_name = getEndPointPath();
          int index = m_name.find('.');
          if(index != std::string::npos)
            m_name = m_name.substr(index + 1, m_name.length());
        }
        return m_name.c_str();
      }
      virtual char const *getDataType() const = 0;
      virtual char const *getResolvedType() const = 0;

      // EndPoint - Default Values

      virtual FabricCore::RTVal getDefaultValue( char const * dataType = NULL ) const = 0;
      virtual void setDefaultValue( FabricCore::RTVal const &value ) = 0;

      // EndPoint - Connections

      bool canConnect( EndPointPtr dst ) const
      {
        FabricCore::DFGExec(getWrappedCoreExec()).canConnect(
          getEndPointPath(), dst->getEndPointPath()
        );
      }

      void connect( EndPointPtr dst )
      {
        getWrappedCoreExec().connect(
          getEndPointPath(), dst->getEndPointPath()
        );
      }

      void disconnect( EndPointPtr dst )
      {
        getWrappedCoreExec().disconnect(
          getEndPointPath(), dst->getEndPointPath()
        );
      }

      void disconnectAll()
      {
        getWrappedCoreExec().disconnectAll(
          getEndPointPath()
        );
      }

      bool isConnected() const
      {
        // todo: this needs cleanup
        return FabricCore::DFGExec(getWrappedCoreExec()).isConnected(getEndPointPath(), "");
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

      static EndPointPtr Create(
        FabricCore::DFGBinding const &binding,
        FabricCore::DFGExec const &exec,
        char const *execPath,
        char const *endPointPath
      );

    private:

      mutable std::string m_name;
      std::string m_endPointPath;

    };

  };

};


#endif // __DFGWrapper_EndPoint__
