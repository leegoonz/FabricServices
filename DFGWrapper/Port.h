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
      friend class GraphExecutable;
      friend class Pin;
      friend class Connection;
      friend class View;

    public:

      Port(const Port & other);
      virtual ~Port();

      bool isValid() const;
      FabricCore::DFGBinding getWrappedCoreBinding() const;

      std::string getPath() const;
      std::string getTitle() const;
      void setTitle(char const *title);
      FabricCore::DFGPortType getPortType();
      std::string getDataType();

      virtual std::string getDesc();

      virtual bool canConnectTo(Port other);
      virtual void connect(const Port & other);
      virtual void disconnect(const Port & other);

      void setDefaultValue(FabricCore::RTVal defaultValue);

    protected:
      
      Port(FabricCore::DFGBinding binding, std::string path, std::string portType = "", std::string dataType = "");

    private:

      FabricCore::DFGBinding m_binding;      
      std::string m_path;
      std::string m_portType;
      std::string m_dataType;
    };

  };

};


#endif // __DFGWrapper_Port__
