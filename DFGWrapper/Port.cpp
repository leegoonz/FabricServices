// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

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

void Port::setName(char const *name)
{
  std::string path = getPath();
  std::string oldName = getName();
  if(name == oldName)
    return;

  std::string newName = m_binding.rename(path.c_str(), name).getCString();
  if(path.rfind('.') != std::string::npos)
    path.substr(0, path.rfind('.')) + newName;
  else
    m_path = newName;
}

FabricCore::DFGPortType Port::getPortType()
{
  if(m_portType.length() == 0)
  {
    FabricCore::Variant descVar = FabricCore::Variant::CreateFromJSON(getDesc().c_str());
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
    if(typeVar->isString())
      m_dataType = typeVar->getStringData();
  }
  return m_dataType;
}

std::string Port::getDesc()
{
  return m_binding.getDesc(m_path.c_str()).getCString();
}

bool Port::canConnectTo(Port other)
{
  if(getDataType() == other.getDataType())
    return true;

  // todo: delegate this to the core
  return false;
}

void Port::connect(const Port & other)
{
  m_binding.connect(m_path.c_str(), other.m_path.c_str());
}

void Port::disconnect(const Port & other)
{
  m_binding.disconnect(m_path.c_str(), other.m_path.c_str());
}

void Port::setDefaultValue(FabricCore::RTVal defaultValue)
{
  m_binding.setPortDefaultValue(m_path.c_str(), defaultValue);
}

