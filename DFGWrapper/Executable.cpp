// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "Executable.h"

using namespace FabricServices::DFGWrapper;

Executable::Executable()
{
}

Executable::Executable(
  FabricCore::DFGBinding binding,
  char const *execPath
  )
{
  m_binding = binding;
  m_execPath = execPath;
}

Executable::Executable(const Executable & other)
{
  m_binding = other.m_binding;
  m_execPath = other.m_execPath;
  m_objectType = other.m_objectType;
}

Executable::~Executable()
{
}

bool Executable::isValid()
{
  if(!m_binding.isValid())
    return false;
  try
  {
    getDesc();
    return true;
  }
  catch(FabricCore::Exception e)
  {
  }
  return false;
}

std::string Executable::getDesc()
{
  return m_binding.getExecDesc(getExecPath()).getCString();
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

std::string Executable::getTitle()
{
  FabricCore::Variant descVar = FabricCore::Variant::CreateFromJSON(getDesc().c_str());
  return descVar.getDictValue("title")->getStringData();    
}

std::vector<Port> Executable::getPorts()
{
  std::vector<Port> result;

  FabricCore::Variant descVar = FabricCore::Variant::CreateFromJSON(getDesc().c_str());
  const FabricCore::Variant * portsVar = descVar.getDictValue("ports");
  for(uint32_t i=0;i<portsVar->getArraySize();i++)
  {
    const FabricCore::Variant * portVar = portsVar->getArrayElement(i);
    const FabricCore::Variant * nameVar = portVar->getDictValue("name");
    std::string nameStr = nameVar->getStringData();
    result.push_back(
      Port( getWrappedCoreBinding(), getExecPath(), nameStr.c_str() )
      );
  }
  return result;
}

Port Executable::getPort(char const * portPath)
{
  return Port(
    getWrappedCoreBinding(),
    getExecPath(),
    portPath
    );
}

Port Executable::getPort(uint32_t index)
{
  return getPorts()[index];
}

void Executable::removePort(Port port)
{
  removePort(port.getName().c_str());
}

void Executable::removePort(char const * portPath)
{
  m_binding.removePort( getExecPath(), portPath );
}

void Executable::removePort(uint32_t index)
{
  removePort(getPorts()[index]);
}

std::vector<std::string> Executable::getErrors()
{
  std::vector<std::string> result;
  FabricCore::Variant descVar = FabricCore::Variant::CreateFromJSON(getDesc().c_str());
  const FabricCore::Variant * errorsVar = descVar.getDictValue("errors");
  if(!errorsVar)
    return result;
  for(uint32_t i=0;i<errorsVar->getArraySize();i++)
  {
    const FabricCore::Variant * errorVar = errorsVar->getArrayElement(i);
    std::string errorStr = errorVar->getStringData();
    result.push_back(errorStr);
  }
  return result;
}

std::string Executable::exportJSON()
{
  return m_binding.exportJSON(getExecPath()).getCString();
}

FEC_DFGCacheRule Executable::getCacheRule() const
{
  return m_binding.getExecCacheRule(getExecPath());
}

void Executable::setCacheRule(FEC_DFGCacheRule rule)
{
  m_binding.setExecCacheRule(getExecPath(), rule);
}

std::string Executable::getMetadata(char const * key)
{
  return m_binding.getExecMetadata(getExecPath(), key);
}

void Executable::setMetadata(char const *key, char const * metadata, bool canUndo)
{
  return m_binding.setExecMetadata(getExecPath(), key, metadata, canUndo);
}

void Executable::addExtensionDependency(char const * ext)
{
  m_binding.addExtDep(getExecPath(), ext);
}

std::string Executable::getImportPathname()
{
  return m_binding.getImportPathname(getExecPath());
}

void Executable::setImportPathname( char const *importPathname )
{
  m_binding.setImportPathname(getExecPath(), importPathname);
}

Port Executable::addPort(char const *title, FabricCore::DFGPortType portType, char const *dataType)
{
  char const *portPath = m_binding.addPort(getExecPath(), title, portType, dataType);
  return Port(m_binding, getExecPath(), portPath);
}

void Executable::attachPreset(char const *parentPresetPath, char const *desiredName)
{
  m_binding.attachPreset(getExecPath(), parentPresetPath, desiredName);
}
