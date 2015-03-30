// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "Port.h"

using namespace FabricServices::DFGWrapper;

Port::Port(FabricCore::DFGBinding binding, FabricCore::DFGExec exec, char const * execPath, char const * portPath)
: EndPoint(binding, exec, execPath, portPath)
{
}

Port::Port(const EndPoint & other)
: EndPoint(other)
{
}

Port::Port(const Port & other)
: EndPoint(other)
{
}

Port::~Port()
{
}

std::string Port::getDesc()
{
  return m_exec.getPortDesc(getPortPath()).getCString();
}

char const *Port::getMetadata(char const * key) const
{
  return FabricCore::DFGExec(m_exec).getPortMetadata(getPortPath(), key);
}

void Port::setMetadata(char const * key, char const * value, bool canUndo)
{
  m_exec.setPortMetadata(getPortPath(), key, value, canUndo);
}

char const *Port::getName() const
{
  return getPortPath();
}

char const *Port::getDataType() const
{
  // todo...
  return NULL;
}

char const *Port::getResolvedType() const
{
  return FabricCore::DFGExec(m_exec).getPortResolvedType(getPortPath());
}

char const *Port::rename(char const * name)
{
  return m_exec.renamePort(getName(), name);
}

FabricCore::RTVal Port::getDefaultValue( char const * dataType ) const
{
  return FabricCore::DFGExec(m_exec).getPortDefaultValue(getPortPath(), dataType);
}

void Port::setDefaultValue( FabricCore::RTVal const &value )
{
  m_exec.setPortDefaultValue(getPortPath(), value);
}
