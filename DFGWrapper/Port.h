// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __DFGWrapper_Port__
#define __DFGWrapper_Port__

#include <FabricCore.h>

namespace FabricServices
{

  namespace DFGWrapper
  {

    class Port
    {
      friend class Binding;

    public:

      Port(const Port & other);
      virtual ~Port();

      FabricCore::DFGBinding getWrappedCoreBinding() const;

      // void connect(char const *srcPath, char const *dstPath);
      // void disconnect(char const *srcPath, char const *dstPath);
      // void addDebugPin(char const *path);
      // RTVal getDebugPinValue(char const *path);
      // void removeDebugPin(char const *path);
      // void setPinDefaultValue(char const *path, RTVal defaultValue);

    protected:
      
      Port(FabricCore::DFGBinding binding, std::string path);

    private:

      FabricCore::DFGBinding m_binding;      
      std::string m_path;
    };

  };

};


#endif // __DFGWrapper_Port__
