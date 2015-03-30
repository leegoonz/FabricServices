// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "Node.h"
#include "GraphExecutable.h"
#include "FuncExecutable.h"

using namespace FabricServices::DFGWrapper;

Node::Node()
{
}

Node::Node(FabricCore::DFGBinding binding, FabricCore::DFGExec parentExec, char const * execPath, char const * nodePath)
: Element(binding, parentExec, nodePath)
{
  m_execPath = execPath;
}

Node::Node(const Node & other)
: Element(other)
{
}

Node::~Node()
{
}

FabricCore::DFGBinding Node::getWrappedCoreBinding() const
{
  return m_binding;
}

Executable Node::getParentExecutable()
{
  return Executable(m_binding, m_exec, m_execPath.c_str());
}

Executable Node::getExecutable()
{
  return getParentExecutable().getSubExec(getNodePath());
}

std::string Node::getDesc()
{
  return m_exec.getNodeDesc(getNodePath()).getCString();
}

std::string Node::getTitle()
{
  // todo
  FabricCore::Variant descVar = FabricCore::Variant::CreateFromJSON(getDesc().c_str());
  return descVar.getDictValue("title")->getStringData();    
}

void Node::setTitle(char const *title)
{
  // todo
  // m_binding.setTitle(getNodePath(), title);
}

std::vector<std::string> Node::getDataTypes()
{
  std::vector<std::string> result;
  // todo
  // FabricCore::Variant descVar = FabricCore::Variant::CreateFromJSON(getDesc().c_str());
  // const FabricCore::Variant * typesVar = descVar.getDictValue("types");
  // for(uint32_t i=0;i<typesVar->getArraySize();i++)
  // {
  //   const FabricCore::Variant * typeVar = typesVar->getArrayElement(i);
  //   if(typeVar->isString())
  //     result.push_back(typeVar->getStringData());
  //   else
  //     result.push_back("");
  // }
  return result;
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

// todo
// std::vector<Pin> Node::getPins()
// {
//   std::vector<Pin> result;

//   FabricCore::Variant descVar = FabricCore::Variant::CreateFromJSON(getDesc().c_str());
//   const FabricCore::Variant * pinsVar = descVar.getDictValue("pins");
//   for(uint32_t i=0;i<pinsVar->getArraySize();i++)
//   {
//     const FabricCore::Variant * pinVar = pinsVar->getArrayElement(i);
//     const FabricCore::Variant * nameVar = pinVar->getDictValue("name");
//     std::string nameStr = nameVar->getStringData();
//     result.push_back(Pin(getWrappedCoreBinding(), getPath() + "." + nameStr));
//   }
//   return result;
// }

// Pin Node::getPin(char const * name)
// {
//   std::string prefix = getPath();
//   if(prefix.length() > 0)
//     prefix += ".";
//   return Pin(m_binding, prefix + name);
// }

// Pin Node::getPin(uint32_t index)
// {
//   return getPins()[index];
// }
