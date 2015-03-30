// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "Pin.h"
#include "Node.h"

using namespace FabricServices::DFGWrapper;

Pin::Pin(FabricCore::DFGBinding binding, FabricCore::DFGExec exec, char const * execPath, char const * pinPath)
: EndPoint(binding, exec, execPath, pinPath)
{
}

Pin::Pin(const EndPoint & other)
: EndPoint(other)
{
}

Pin::Pin(const Pin & other)
: EndPoint(other)
{
}

Pin::~Pin()
{
}

std::string Pin::getDesc()
{
  return m_exec.getPinDesc(getPinPath()).getCString();
}

char const *Pin::getMetadata(char const * key) const
{
  return FabricCore::DFGExec(m_exec).getPinMetadata(getPinPath(), key);
}

void Pin::setMetadata(char const * key, char const * value, bool canUndo)
{
  m_exec.setPinMetadata(getPinPath(), key, value, canUndo);
}

void Pin::addDebugPin()
{
  m_exec.addDebugPin(getPinPath());
}

FabricCore::RTVal Pin::getDebugPinValue()
{
  return m_exec.getDebugPinValue(getPinPath());
}

void Pin::removeDebugPin()
{
  m_exec.removeDebugPin(getPinPath());
}

FabricCore::RTVal Pin::getDefaultValue( char const * dataType ) const
{
  return FabricCore::DFGExec(m_exec).getPinDefaultValue(getPinPath(), dataType);
}

void Pin::setDefaultValue( FabricCore::RTVal const &value )
{
  m_exec.setPinDefaultValue(getPinPath(), value);
}
