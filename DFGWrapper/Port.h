// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __DFGWrapper_Port__
#define __DFGWrapper_Port__

#include <FabricCore.h>
#include <string>
#include <vector>

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
      std::string getName() const;
      std::string setName(char const *name);
      FabricCore::DFGPortType getPortType();
      std::string getDataType();
      bool isArray();
      unsigned int getArraySize();

      virtual std::string getDesc();

      virtual bool hasMetadata(char const * key);
      virtual std::string getMetadata(char const * key);
      virtual void setMetadata(char const * key, char const * metadata, bool canUndo);
      virtual bool hasOption(char const * key);
      virtual FabricCore::Variant getOption(char const * key);
      virtual void setOption(char const * key, const FabricCore::Variant * var);

      virtual bool canConnect(Port other);
      virtual void connect(const Port & other);
      virtual void disconnect(const Port & other);
      virtual bool isConnected();
      virtual std::vector<std::string> getSources();
      virtual std::vector<std::string> getDestinations();

      virtual FabricCore::RTVal getDefaultValue(char const * dataType = NULL);
      virtual void setDefaultValue(FabricCore::RTVal value);

      virtual FabricCore::RTVal getRTVal();
      virtual void setRTVal(FabricCore::RTVal value);

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
