// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __DFGWrapper_Pin__
#define __DFGWrapper_Pin__

#include <FabricCore.h>
#include <string>

#include "EndPoint.h"

namespace FabricServices
{

  namespace DFGWrapper
  {
    class Pin;
    typedef FTL::SharedPtr<Pin> PinPtr;
    
    class Pin : public EndPoint
    {
      friend class Node;
      friend class View;
      friend class EndPoint;

    public:

      virtual bool isPin() const { return true; }

      static PinPtr Create(FabricCore::DFGBinding binding, FabricCore::DFGExec exec, char const * execPath, char const * pinPath);
      virtual ~Pin();

      char const *getPinPath() const
        { return getEndPointPath(); }

      virtual std::string getDesc();
      virtual char const *getMetadata(char const * key) const;
      virtual void setMetadata(char const * key, char const * value, bool canUndo = false);

      virtual char const *getName() const
      {
        return FabricCore::DFGExec(getWrappedCoreExec()).getPinName(getPinPath());
      }
      virtual char const *getResolvedType() const
      {
        return FabricCore::DFGExec(getWrappedCoreExec()).getPinResolvedType(getPinPath());
      }

      void addDebugPin();
      FabricCore::RTVal getDebugPinValue();
      void removeDebugPin();

      virtual FabricCore::RTVal getDefaultValue( char const * dataType = NULL ) const;
      virtual void setDefaultValue( FabricCore::RTVal const &value );

    protected:
      
      Pin(FabricCore::DFGBinding binding, FabricCore::DFGExec exec, char const * execPath, char const * pinPath);

    };

  };

};


#endif // __DFGWrapper_Pin__
