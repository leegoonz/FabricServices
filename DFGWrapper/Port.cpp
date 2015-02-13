// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "Port.h"

using namespace FabricServices::DFGWrapper;

Port::Port(FabricCore::DFGBinding binding, std::string path, std::string portType, std::string dataType)
{
  m_binding = binding;
  m_path = path;
  m_portType = portType;
  m_dataType = dataType;
}

Port::Port(const Port & other)
{
  m_binding = other.m_binding;
  m_path = other.m_path;
  m_portType = other.m_portType;
  m_dataType = other.m_dataType;
}

Port::~Port()
{
}

bool Port::isValid() const
{
  return m_binding.isValid();
}

FabricCore::DFGBinding Port::getWrappedCoreBinding() const
{
  return m_binding;
}

std::string Port::getPath() const
{
  return m_path;
}

std::string Port::getName() const
{
  if(m_path.length() == 0)
    return "";
  int pos = m_path.rfind('.');
  if(pos == std::string::npos)
    return m_path;
  return m_path.substr(pos+1, m_path.length());
}

std::string Port::setName(char const *name)
{
  std::string path = getPath();
  std::string oldName = getName();
  if(name == oldName)
    return oldName;

  std::string newName = m_binding.rename(path.c_str(), name).getCString();
  if(path.rfind('.') != std::string::npos)
    m_path = path.substr(0, path.rfind('.')) + newName;
  else
    m_path = newName;
  return newName;
}

FabricCore::DFGPortType Port::getPortType()
{
  if(m_portType.length() == 0)
  {
    FabricCore::Variant descVar = FabricCore::Variant::CreateFromJSON(Port::getDesc().c_str());
    const FabricCore::Variant * typeVar = descVar.getDictValue("portType");
    m_portType = typeVar->getStringData();
  }
  if(m_portType == "In")
    return FabricCore::DFGPortType_In;
  if(m_portType == "Out")
    return FabricCore::DFGPortType_Out;
  return FabricCore::DFGPortType_IO;
}

std::string Port::getDataType()
{
  if(m_dataType.length() == 0)
  {
    FabricCore::Variant descVar = FabricCore::Variant::CreateFromJSON(getDesc().c_str());
    const FabricCore::Variant * typeVar = descVar.getDictValue("type");
    if(typeVar)
      if(typeVar->isString())
        m_dataType = typeVar->getStringData();
    if(m_dataType.length() == 0)
    {
      typeVar = descVar.getDictValue("dataType");
      if(typeVar)
        if(typeVar->isString())
          m_dataType = typeVar->getStringData();
    }
  }
  return m_dataType;
}

bool Port::isArray()
{
  if(m_dataType.length() == 0)
    getDataType();
  return m_dataType.substr(m_dataType.length()-2, 2) == "[]";
}

unsigned int Port::getArraySize()
{
  return getRTVal().getArraySize();
}

std::string Port::getDesc()
{
  return m_binding.getDesc(m_path.c_str()).getCString();
}

bool Port::hasMetadata(char const * key)
{
  return getMetadata(key).length() > 0;
}

std::string Port::getMetadata(char const * key)
{
  const char * md = m_binding.getMetadata(m_path.c_str(), key);
  if(md)
    return md;
  return "";
}

void Port::setMetadata(char const *key, char const * metadata, bool canUndo)
{
  return m_binding.setMetadata(m_path.c_str(), key, metadata, canUndo);
}

bool Port::hasOption(char const * key)
{
  return hasMetadata(key);
}

FabricCore::Variant Port::getOption(char const * key)
{
  std::string md = getMetadata(key);
  if(md.length() > 0)
    return FabricCore::Variant::CreateFromJSON(md.c_str());
  return FabricCore::Variant();
}

void Port::setOption(char const * key, const FabricCore::Variant * var)
{
  if(!var)
    return;
  setMetadata(key, var->getJSONEncoding().getStringData(), false);
}

bool Port::canConnect(Port other)
{
  FabricCore::DFGStringResult result = m_binding.canConnect(m_path.c_str(), other.m_path.c_str());
  return result.getCString() == NULL;
}

void Port::connect(const Port & other)
{
  m_binding.connect(m_path.c_str(), other.m_path.c_str());
}

void Port::disconnect(const Port & other)
{
  m_binding.disconnect(m_path.c_str(), other.m_path.c_str());
}

bool Port::isConnected()
{
  return getSources().size() > 0 || getDestinations().size() > 0;
}

std::vector<std::string> Port::getSources()
{
  std::vector<std::string> result;
  FabricCore::Variant descVar = FabricCore::Variant::CreateFromJSON(getDesc().c_str());
  const FabricCore::Variant * connectionsVar = descVar.getDictValue("connections");
  if(connectionsVar)
  {
    for(FabricCore::Variant::DictIter connectionIter(*connectionsVar); !connectionIter.isDone(); connectionIter.next())
    {
      std::string name = connectionIter.getKey()->getStringData();
      if(name != "src")
        continue;
      const FabricCore::Variant * sourceVar = connectionIter.getValue();
      if(sourceVar->isString())
      {
        result.push_back(sourceVar->getStringData());
      }
    }
  }
  return result;
}

std::vector<std::string> Port::getDestinations()
{
  std::vector<std::string> result;
  FabricCore::Variant descVar = FabricCore::Variant::CreateFromJSON(getDesc().c_str());
  const FabricCore::Variant * connectionsVar = descVar.getDictValue("dsts");
  if(connectionsVar)
  {
    for(unsigned int i=0;i<connectionsVar->getArraySize();i++)
    {
      const FabricCore::Variant * connectionVar = connectionsVar->getArrayElement(i);
      if(connectionVar->isString())
      {
        std::string name = connectionVar->getStringData();
        if(name != getName())
          result.push_back(name);
      }
    }
  }
  return result;
}

FabricCore::RTVal Port::getDefaultValue(char const * dataType)
{
  FabricCore::Variant descVar = FabricCore::Variant::CreateFromJSON(Port::getDesc().c_str());
  const FabricCore::Variant * defaultValuesVar = descVar.getDictValue("defaultValues");
  if(defaultValuesVar)
  {
    std::string dataType = getDataType();
    const FabricCore::Variant * defaultValueVar = defaultValuesVar->getDictValue(dataType.c_str());
    if(defaultValueVar)
    {
      FabricCore::DFGHost host = getWrappedCoreBinding().getHost();
      FabricCore::Context context = host.getContext();
      return FabricCore::ConstructRTValFromJSON(context, dataType.c_str(), defaultValueVar->getJSONEncoding().getStringData());
    }
  }
  
  return FabricCore::RTVal();
}

void Port::setDefaultValue(FabricCore::RTVal value)
{
  m_binding.setPortDefaultValue(m_path.c_str(), value);
}

FabricCore::RTVal Port::getRTVal()
{
  return m_binding.getArgValue(m_path.c_str());
}

void Port::setRTVal(FabricCore::RTVal value)
{
  // todo: this type conversion should not be required
  std::string dataType = getRTVal().getTypeName().getStringCString();
  if(dataType != value.getTypeName().getStringCString())
  {
    FabricCore::DFGHost host = getWrappedCoreBinding().getHost();
    FabricCore::Context context = host.getContext();
    value = FabricCore::RTVal::Construct(context, dataType.c_str(), 1, &value);
  }

  m_binding.setArgValue(m_path.c_str(), value);
}

