// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __DFGWrapper_Port__
#define __DFGWrapper_Port__

#include <FabricCore.h>
#include <string>

namespace FabricServices
{

  namespace DFGWrapper
  {

    class Port
    {
      friend class Executable;

    public:

      Port(const Port & other);
      virtual ~Port();

      FabricCore::DFGBinding getWrappedCoreBinding() const;

      std::string getPath() const;
      std::string getTitle() const;

      std::string getDesc();

      void connect(const Port & other);
      void disconnect(const Port & other);
      void setDefaultValue(FabricCore::RTVal defaultValue);
      void addDebugPin();
      FabricCore::RTVal getDebugPinValue();
      void removeDebugPin();
      void setPinDefaultValue(FabricCore::RTVal defaultValue);

    protected:
      
      Port(FabricCore::DFGBinding binding, std::string path);

    private:

      FabricCore::DFGBinding m_binding;      
      std::string m_path;
    };

  };

};


#endif // __DFGWrapper_Port__
