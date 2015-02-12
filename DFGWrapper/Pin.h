// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

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
      friend class View;

    public:

      Pin(const Pin & other);
      virtual ~Pin();

      FabricCore::DFGPortType getPinType();

      virtual std::string getDesc();

      virtual std::string getMetadata(char const * key);
      virtual void setMetadata(char const * key, char const * metadata, bool canUndo);

      Port getPort();

      void addDebugPin();
      FabricCore::RTVal getDebugPinValue();
      void removeDebugPin();

      virtual FabricCore::RTVal getDefaultValue(char const * dataType = NULL);
      virtual void setDefaultValue(FabricCore::RTVal value);

    protected:
      
      Pin(FabricCore::DFGBinding binding, std::string path);

    private:
      
      std::string m_pinType;

    };

  };

};


#endif // __DFGWrapper_Pin__
