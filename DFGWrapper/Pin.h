// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __DFGWrapper_Pin__
#define __DFGWrapper_Pin__

#include <FabricCore.h>
#include <string>
#include <vector>

#include "EndPoint.h"

namespace FabricServices
{

  namespace DFGWrapper
  {
    class Node;
    typedef FTL::SharedPtr<Node> NodePtr;
    typedef std::vector<NodePtr> NodeList;

    class Port;
    typedef FTL::SharedPtr<Port> PortPtr;
    typedef std::vector<PortPtr> ExecPortList;

    class Pin;
    typedef FTL::SharedPtr<Pin> PinPtr;
    typedef std::vector<PinPtr> PinList;
    
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
        char const * result = FabricCore::DFGExec(getWrappedCoreExec()).getPinResolvedType(getPinPath());
        if(result)
          return result;
        return "";
      }

      void addDebugPin();
      FabricCore::RTVal getDebugPinValue();
      void removeDebugPin();

      virtual FabricCore::RTVal getDefaultValue( char const * dataType = NULL ) const;
      virtual void setDefaultValue( FabricCore::RTVal const &value );

      NodePtr getNode();
      PortPtr getPort();

    protected:
      
      Pin(FabricCore::DFGBinding binding, FabricCore::DFGExec exec, char const * execPath, char const * pinPath);

    };

  };

};


#endif // __DFGWrapper_Pin__
