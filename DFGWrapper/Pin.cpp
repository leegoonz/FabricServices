// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "Pin.h"
#include "ExecPort.h"
#include "Node.h"

using namespace FabricServices::DFGWrapper;

Pin::Pin(FabricCore::DFGBinding binding, FabricCore::DFGExec exec, char const * execPath, char const * pinPath)
: EndPoint(binding, exec, execPath, pinPath)
{
}

PinPtr Pin::Create(FabricCore::DFGBinding binding, FabricCore::DFGExec exec, char const * execPath, char const * pinPath)
{
  return new Pin(binding, exec, execPath, pinPath);
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

NodePtr Pin::getNode()
{
  std::string nodeName = getPinPath();
  int pos = nodeName.find('.');
  if(pos == std::string::npos)
    return NodePtr();
  nodeName = nodeName.substr(0, pos);
  return new Node(m_binding, m_exec, getElementPath(), nodeName.c_str());
}

ExecPortPtr Pin::getPort()
{
  NodePtr node = getNode();
  if(!node)
    return ExecPortPtr();
  return node->getExecutable()->getPort(getName());
}
