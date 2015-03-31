// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "Node.h"
#include "GraphExecutable.h"
#include "FuncExecutable.h"

using namespace FabricServices::DFGWrapper;

NodePtr Node::Create(FabricCore::DFGBinding binding, FabricCore::DFGExec parentExec, char const * execPath, char const * nodePath)
{
  return new Node(binding, parentExec, execPath, nodePath);
}

Node::Node(FabricCore::DFGBinding binding, FabricCore::DFGExec parentExec, char const * execPath, char const * nodePath)
: Element(binding, parentExec, nodePath)
{
  m_execPath = execPath;
}

Node::~Node()
{
}

GraphExecutablePtr Node::getOwningGraphExecutable()
{
  return GraphExecutablePtr::StaticCast(
    Executable::Create(m_binding, m_exec, m_execPath.c_str())
    );
}

ExecutablePtr Node::getExecutable()
{
  return getOwningGraphExecutable()->getSubExec(getNodePath());
}

std::string Node::getDesc()
{
  return m_exec.getNodeDesc(getNodePath()).getCString();
}

char const* Node::getTitle()
{
  return m_exec.getNodeTitle(getNodePath());
}

void Node::setTitle(char const *title)
{
  m_exec.setNodeTitle(getNodePath(), title);
}

FEC_DFGCacheRule Node::getCacheRule() const
{
  return m_exec.getNodeCacheRule(getNodePath());
}

void Node::setCacheRule(FEC_DFGCacheRule rule)
{
  m_exec.setNodeCacheRule(getNodePath(), rule);
}

char const *Node::getMetadata(char const * key) const
{
  return FabricCore::DFGExec(m_exec).getNodeMetadata(getNodePath(), key);
}

void Node::setMetadata(char const *key, char const * metadata, bool canUndo)
{
  return m_exec.setNodeMetadata(getNodePath(), key, metadata, canUndo);
}

PinList Node::getPins()
{
  FabricCore::DFGExec exec = m_exec.getSubExec(getNodePath());
  PinList result;
  for(unsigned int i=0;i<exec.getPortCount();i++)
  {
    std::string path = getNodePath();
    path += ".";
    path += exec.getPortName(i);
    result.push_back(new Pin(m_binding, m_exec, m_execPath.c_str(), path.c_str()));
  }
  return result;
}

PinPtr Node::getPin(char const * name)
{
  std::string path = getNodePath();
  if(path.length() > 0)
    path += ".";
  path += name;
  return new Pin(m_binding, m_exec, m_execPath.c_str(), path.c_str());
}

PinPtr Node::getPin(uint32_t index)
{
  return getPins()[index];
}
