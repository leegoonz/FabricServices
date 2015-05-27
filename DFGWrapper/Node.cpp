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
  return getOwningGraphExecutable()->getSubExec(getName());
}

std::string Node::getDesc()
{
  return m_exec.getNodeDesc(getName()).getCString();
}

char const* Node::getTitle()
{
  return m_exec.getNodeTitle(getName());
}

void Node::setTitle(char const *title)
{
  m_exec.setNodeTitle(getName(), title);
}

FEC_DFGCacheRule Node::getCacheRule() const
{
  return m_exec.getNodeCacheRule(getName());
}

void Node::setCacheRule(FEC_DFGCacheRule rule)
{
  m_exec.setNodeCacheRule(getName(), rule);
}

char const *Node::getMetadata(char const * key) const
{
  return FabricCore::DFGExec(m_exec).getNodeMetadata(getName(), key);
}

void Node::setMetadata(char const *key, char const * metadata, bool canUndo)
{
  return m_exec.setNodeMetadata(getName(), key, metadata, canUndo);
}

NodePortList Node::getPorts()
{
  FabricCore::DFGExec exec = m_exec.getSubExec(getName());
  NodePortList result;
  for(unsigned int i=0;i<exec.getExecPortCount();i++)
  {
    std::string path = getName();
    path += ".";
    path += exec.getExecPortName(i);
    result.push_back(new NodePort(m_binding, m_exec, m_execPath.c_str(), path.c_str()));
  }
  return result;
}

NodePortPtr Node::getPort(char const * name)
{
  std::string path = getName();
  if(path.length() > 0)
    path += ".";
  path += name;
  return new NodePort(m_binding, m_exec, m_execPath.c_str(), path.c_str());
}

NodePortPtr Node::getPort(uint32_t index)
{
  return getPorts()[index];
}
