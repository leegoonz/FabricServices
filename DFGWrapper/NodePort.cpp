// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "NodePort.h"
#include "ExecPort.h"
#include "Node.h"

using namespace FabricServices::DFGWrapper;

NodePort::NodePort(FabricCore::DFGBinding binding, FabricCore::DFGExec exec, char const * execPath, char const * nodePortPath)
: Port(binding, exec, execPath, nodePortPath)
{
}

NodePortPtr NodePort::Create(FabricCore::DFGBinding binding, FabricCore::DFGExec exec, char const * execPath, char const * nodePortPath)
{
  return new NodePort(binding, exec, execPath, nodePortPath);
}

NodePort::~NodePort()
{
}

std::string NodePort::getDesc()
{
  return m_exec.getNodePortDesc(getNodePortPath()).getCString();
}

char const *NodePort::getMetadata(char const * key) const
{
  return FabricCore::DFGExec(m_exec).getNodePortMetadata(getNodePortPath(), key);
}

void NodePort::setMetadata(char const * key, char const * value, bool canUndo)
{
  m_exec.setNodePortMetadata(getNodePortPath(), key, value, canUndo);
}

void NodePort::addDebugNodePort()
{
  m_exec.addDebugNodePort(getNodePortPath());
}

FabricCore::RTVal NodePort::getDebugNodePortValue()
{
  return m_exec.getDebugNodePortValue(getNodePortPath());
}

void NodePort::removeDebugNodePort()
{
  m_exec.removeDebugNodePort(getNodePortPath());
}

FabricCore::RTVal NodePort::getDefaultValue( char const * dataType ) const
{
  return FabricCore::DFGExec(m_exec).getNodePortDefaultValue(getNodePortPath(), dataType);
}

void NodePort::setDefaultValue( FabricCore::RTVal const &value )
{
  m_exec.setNodePortDefaultValue(getNodePortPath(), value);
}

NodePtr NodePort::getNode()
{
  std::string nodeName = getNodePortPath();
  int pos = nodeName.find('.');
  if(pos == std::string::npos)
    return NodePtr();
  nodeName = nodeName.substr(0, pos);
  return new Node(m_binding, m_exec, getElementPath(), nodeName.c_str());
}

ExecPortPtr NodePort::getPort()
{
  NodePtr node = getNode();
  if(!node)
    return ExecPortPtr();
  return node->getExecutable()->getPort(getName());
}
