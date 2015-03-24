// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __DFGWrapper_Port__
#define __DFGWrapper_Port__

#include "EndPoint.h"

namespace FabricServices
{

  namespace DFGWrapper
  {
    class Exec;

    class Port : public EndPoint
    {
      
      friend class Exec;

    public:

      // Element - Type

      virtual bool isPort() const { return true; }

      // Element - Validity

      virtual bool isValid() const
      {
        return getWrappedCoreBinding()->isValidPort(
          getExecPath(), getPortPath()
          );
      }
      
      // Element - Desc

      virtual std::string getDesc() const
      {
        FabricCore::StringResult result =
          getWrappedCoreBinding()->getPortDesc(
            getExecPath(), getPortPath()
            );
        return std::string(
          result->getStringData(), result->getStringLength()
          );
      }

      // Element - Metadata

      virtual char const *getMetadata(char const * key) const
      {
        return getWrappedCoreBinding()->getPortMetadata(
          getExecPath(), getPortPath(), key
          );
      }
      virtual void setMetadata(char const * key, char const * value, bool canUndo)
      {
        getWrappedCoreBinding()->setPortMetadata(
          getExecPath(), getPortPath(), key, value, canUndo
          );
      }

      virtual char const *getDataType() const;

      // EndPoint - Default Values

      virtual FabricCore::RTVal getDefaultValue( char const * type ) const
      {
        return getWrappedCoreBinding()->getPortDefaultValue(
          getExecPath(), getPortPath(), type
          );
      }

      virtual void setDefaultValue( FabricCore::RTVal const &value )
      {
        getWrappedCoreBinding()->setPortDefaultValue(
          getExecPath(), getPortPath(), value
          );
      }

      // Port - Accessors

      char const *getPortPath() const
        { return getEndPointPath(); }

      char const *getName() const
        { return getPortPath(); }
      char const *setName(char const *desiredName)
      {
        char const *actualName =
          getWrappedCoreBinding()->renamePort(
            getExecPath(), getPortPath(), desiredName
            );
        m_portPath = actualName;
        return actualName;
      }

      FabricCore::DFGPortType getPortType() const
      {
        return getWrappedCoreBinding()->getPortType(
          getExecPath(), getPortPath()
          );
      }

      // Port - RTVals

      FabricCore::RTVal getRTVal()
      {
        if ( !getExecPath()[0] )
          return getWrappedCoreBinding()->getArgValue( getPortPath() );
        else
          return FabricCore::RTVal();
      }

      void setRTVal(FabricCore::RTVal const &value)
      {
        if ( !getExecPath()[0] )
          getWrappedCoreBinding()->setArgValue( getPortPath, value );
      }

    protected:
      
      Port(
        FabricCore::DFGBinding binding,
        char const *execPath,
        char const *portPath
        )
        : EndPoint(
          binding,
          execPath,
          portPath
          )
      {
      }

    };

  };

};


#endif // __DFGWrapper_Port__
