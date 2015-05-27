// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "ExecPort.h"

using namespace FabricServices::DFGWrapper;

ExecPort::ExecPort(FabricCore::DFGBinding binding, FabricCore::DFGExec exec, char const * execPath, char const * portPath)
: EndPoint(binding, exec, execPath, portPath)
{
}

ExecPortPtr ExecPort::Create(FabricCore::DFGBinding binding, FabricCore::DFGExec exec, char const * execPath, char const * portPath)
{
  return new ExecPort(binding, exec, execPath, portPath);
}

ExecPort::~ExecPort()
{
}

std::string ExecPort::getDesc()
{
  return m_exec.getExecPortDesc(getExecPortPath()).getCString();
}

char const *ExecPort::getMetadata(char const * key) const
{
  return FabricCore::DFGExec(m_exec).getExecPortMetadata(getExecPortPath(), key);
}

void ExecPort::setMetadata(char const * key, char const * value, bool canUndo)
{
  m_exec.setExecPortMetadata(getExecPortPath(), key, value, canUndo);
}

char const *ExecPort::rename(char const * name)
{
  return m_exec.renameExecPort(getName(), name);
}

FabricCore::RTVal ExecPort::getDefaultValue( char const * dataType ) const
{
  return FabricCore::DFGExec(m_exec).getExecPortDefaultValue(getExecPortPath(), dataType);
}

void ExecPort::setDefaultValue( FabricCore::RTVal const &value )
{
  m_exec.setExecPortDefaultValue(getExecPortPath(), value);
}

FabricCore::RTVal ExecPort::getArgValue()
{
  return m_binding.getArgValue(getExecPortPath());
}

void ExecPort::setArgValue( FabricCore::RTVal const &value )
{
  m_binding.setArgValue(getExecPortPath(), value);
}
