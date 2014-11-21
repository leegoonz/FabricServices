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

std::string Executable::getImportPathName()
{
  return m_binding.getImportPathname(m_path.c_str());
}

Port Executable::addPort(char const *title, FabricCore::DFGPortType portType, char const *dataType)
{
  std::string result = m_binding.addPort(m_path.c_str(), title, portType, dataType).getCString();
  return Port(m_binding, m_path + "." + result);
}
