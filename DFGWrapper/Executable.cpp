// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "Executable.h"

using namespace FabricServices::DFGWrapper;

Executable::Executable(FabricCore::DFGBinding binding, std::string path)
{
  m_binding = binding;
  m_path = path;
}

Executable::Executable(const Executable & other)
{
  m_binding = other.m_binding;
  m_path = other.m_path;
  m_objectType = other.m_objectType;
}

Executable::~Executable()
{
}

bool Executable::isValid() const
{
  return m_binding.isValid();
}


FabricCore::DFGBinding Executable::getWrappedCoreBinding() const
{
  return m_binding;
}

std::string Executable::getDesc()
{
  return m_binding.getDesc(m_path.c_str()).getCString();
}

std::string Executable::getObjectType()
{
  if(m_objectType.length() == 0)
  {
    FabricCore::Variant descVar = FabricCore::Variant::CreateFromJSON(getDesc().c_str());
    m_objectType = descVar.getDictValue("objectType")->getStringData();    
  }
  return m_objectType;
}

std::string Executable::getPath()
{
  return m_path;
}

std::string Executable::getTitle()
{
  FabricCore::Variant descVar = FabricCore::Variant::CreateFromJSON(getDesc().c_str());
  return descVar.getDictValue("title")->getStringData();    
}

std::vector<Port> Executable::getPorts()
{
  std::vector<Port> result;

  std::string prefix = getPath();
  if(prefix.length() > 0)
    prefix += ".";

  FabricCore::Variant descVar = FabricCore::Variant::CreateFromJSON(getDesc().c_str());
  const FabricCore::Variant * portsVar = descVar.getDictValue("ports");
  for(uint32_t i=0;i<portsVar->getArraySize();i++)
  {
    const FabricCore::Variant * portVar = portsVar->getArrayElement(i);
    const FabricCore::Variant * titleVar = portVar->getDictValue("title");
    std::string titleStr = titleVar->getStringData();
    result.push_back(Port(getWrappedCoreBinding(), prefix + titleStr));
  }
  return result;
}

Port Executable::getPort(char const * name)
{
  std::string prefix = getPath();
  if(prefix.length() > 0)
    prefix += ".";
  return Port(getWrappedCoreBinding(), prefix + name);
}

Port Executable::getPort(uint32_t index)
{
  return getPorts()[index];
}

void Executable::removePort(Port port)
{
  removePort(port.getTitle().c_str());
}

void Executable::removePort(char const * name)
{
  std::string prefix = getPath();
  if(prefix.length() > 0)
    prefix += ".";
  m_binding.destroy((prefix + name).c_str());
}

void Executable::removePort(uint32_t index)
{
  removePort(getPorts()[index]);
}

std::string Executable::exportJSON()
{
  return m_binding.exportJSON(m_path.c_str()).getCString();
}

std::string Executable::getMetadata(char const * key)
{
  return m_binding.getMetadata(m_path.c_str(), key);
}

void Executable::setMetadata(char const *key, char const * metadata, bool canUndo)
{
  return m_binding.setMetadata(m_path.c_str(), key, metadata, canUndo);
}

void Executable::addExtensionDependency(char const * ext)
{
  m_binding.addExtDep(m_path.c_str(), ext);
}

std::string Executable::getImportPathName()
{
  return m_binding.getImportPathname(m_path.c_str());
}

Port Executable::addPort(char const *title, FabricCore::DFGPortType portType, char const *dataType)
{
  std::string result = m_binding.addPort(m_path.c_str(), title, portType, dataType).getCString();
  return Port(m_binding, result);
}
