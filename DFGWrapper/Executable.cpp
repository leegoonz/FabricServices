// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "Executable.h"

using namespace FabricServices::DFGWrapper;

Executable::Executable()
{
}

Executable::Executable(
  FabricCore::DFGBinding binding,
  FabricCore::DFGExec exec,
  const char * execPath
  )
: Element(binding, exec, execPath)
{
}

Executable::Executable(const Executable & other)
: Element(other)
{
}

Executable::~Executable()
{
}

FabricCore::DFGExecType Executable::getExecType() const
{
  return m_exec.getType();
}

std::string Executable::getDesc()
{
  return m_exec.getDesc().getCString();
}

std::string Executable::getTitle()
{
  return m_exec.getTitle();
}

void Executable::setTitle(const char * title)
{
  m_exec.setTitle(title);
}

Executable Executable::getSubExec(const char * subExecPath)
{
  return Executable(m_binding, m_exec.getSubExec(subExecPath), subExecPath);
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
  return m_exec.exportJSON().getCString();
}

FEC_DFGCacheRule Executable::getCacheRule() const
{
  return m_exec.getCacheRule();
}

void Executable::setCacheRule(FEC_DFGCacheRule rule)
{
  m_exec.setCacheRule(rule);
}

char const *Executable::getMetadata(char const * key) const
{
  return FabricCore::DFGExec(m_exec).getMetadata(key);
}

void Executable::setMetadata(char const *key, char const * metadata, bool canUndo)
{
  return m_exec.setMetadata(key, metadata, canUndo);
}

void Executable::addExtensionDependency(char const * ext)
{
  m_exec.addExtDep(ext);
}

void Executable::removeExtensionDependency(char const * ext)
{
  m_exec.removeExtDep(ext);
}

std::string Executable::getImportPathname()
{
  return m_exec.getImportPathname();
}

void Executable::setImportPathname( char const *importPathname )
{
  m_exec.setImportPathname(importPathname);
}

std::vector<PortPtr> Executable::getPorts()
{
  std::vector<PortPtr> result;
  for(unsigned int i=0;i<m_exec.getPortCount();i++)
  {
    result.push_back(
      new Port( m_binding, m_exec, getExecPath(), m_exec.getPortName(i) )
    );
  }
  return result;
}

PortPtr Executable::getPort(char const * portPath)
{
  return new Port(
    m_binding,
    m_exec,
    getExecPath(),
    portPath
  );
}

PortPtr Executable::getPort(uint32_t index)
{
  return getPorts()[index];
}

PortPtr Executable::addPort(char const *title, FabricCore::DFGPortType portType, char const *dataType)
{
  char const *portPath = m_exec.addPort(title, portType, dataType);
  return new Port(m_binding, m_exec, getExecPath(), portPath);
}

void Executable::removePort(char const * portPath)
{
  m_exec.removePort( portPath );
}

void Executable::removePort(uint32_t index)
{
  removePort(getPorts()[index]->getName());
}

void Executable::attachPreset(char const *parentPresetPath, char const *desiredName)
{
  m_exec.attachPreset(parentPresetPath, desiredName);
}
