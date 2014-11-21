// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __DFGWrapper_Pin__
#define __DFGWrapper_Pin__

#include <FabricCore.h>
#include <string>

#include "Port.h"

namespace FabricServices
{

  namespace DFGWrapper
  {

    class Pin : public Port
    {
      friend class Node;

    public:

      Pin(const Pin & other);
      virtual ~Pin();

      FabricCore::DFGPortType getPinType();

      virtual std::string getDesc();

      Port getPort();

      void addDebugPin();
      FabricCore::RTVal getDebugPinValue();
      void removeDebugPin();
      void setPinDefaultValue(FabricCore::RTVal defaultValue);

    protected:
      
      Pin(FabricCore::DFGBinding binding, std::string path);

    private:
      
      std::string m_pinType;

    };

  };

};


#endif // __DFGWrapper_Pin__
