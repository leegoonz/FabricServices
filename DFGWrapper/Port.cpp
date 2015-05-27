// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "Port.h"

using namespace FabricServices::DFGWrapper;

Port::Port(FabricCore::DFGBinding binding, FabricCore::DFGExec exec, char const * execPath, char const * portPath)
: EndPoint(binding, exec, execPath, portPath)
{
}

PortPtr Port::Create(FabricCore::DFGBinding binding, FabricCore::DFGExec exec, char const * execPath, char const * portPath)
{
  return new Port(binding, exec, execPath, portPath);
}

Port::~Port()
{
}

std::string Port::getDesc()
{
  return m_exec.getExecPortDesc(getPortPath()).getCString();
}

char const *Port::getMetadata(char const * key) const
{
  return FabricCore::DFGExec(m_exec).getExecPortMetadata(getPortPath(), key);
}

void Port::setMetadata(char const * key, char const * value, bool canUndo)
{
  m_exec.setExecPortMetadata(getPortPath(), key, value, canUndo);
}

char const *Port::rename(char const * name)
{
  return m_exec.renameExecPort(getName(), name);
}

FabricCore::RTVal Port::getDefaultValue( char const * dataType ) const
{
  return FabricCore::DFGExec(m_exec).getExecPortDefaultValue(getPortPath(), dataType);
}

void Port::setDefaultValue( FabricCore::RTVal const &value )
{
  m_exec.setExecPortDefaultValue(getPortPath(), value);
}

FabricCore::RTVal Port::getArgValue()
{
  return m_binding.getArgValue(getPortPath());
}

void Port::setArgValue( FabricCore::RTVal const &value )
{
  m_binding.setArgValue(getPortPath(), value);
}
