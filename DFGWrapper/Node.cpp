// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "Node.h"
#include "GraphExecutable.h"
#include "FuncExecutable.h"

using namespace FabricServices::DFGWrapper;

Node::Node(FabricCore::DFGBinding binding, std::string path)
{
  m_binding = binding;
  m_path = path;
}

Node::Node(const Node & other)
{
  m_binding = other.m_binding;
  m_path = other.m_path;
  m_objectType = other.m_objectType;
}

Node::~Node()
{
}

FabricCore::DFGBinding Node::getWrappedCoreBinding() const
{
  return m_binding;
}

Executable Node::getExecutable()
{
  return Executable(m_binding, m_path);
}

std::string Node::getDesc()
{
  return m_binding.getInstanceDesc(m_path.c_str()).getCString();
}

std::string Node::getObjectType()
{
  if(m_objectType.length() == 0)
  {
    FabricCore::Variant descVar = FabricCore::Variant::CreateFromJSON(getDesc().c_str());
    m_objectType = descVar.getDictValue("objectType")->getStringData();    
  }
  return m_objectType;
}

std::string Node::getPath()
{
  return m_path;
}

std::string Node::getTitle()
{
  FabricCore::Variant descVar = FabricCore::Variant::CreateFromJSON(getDesc().c_str());
  return descVar.getDictValue("title")->getStringData();    
}

void Node::setTitle(char const *title)
{
  m_binding.setTitle(m_path.c_str(), title);
}

std::string Node::getMetadata(char const * key)
{
  return m_binding.getInstanceMetadata(m_path.c_str(), key);
}

void Node::setMetadata(char const *key, char const * metadata, bool canUndo)
{
  return m_binding.setInstanceMetadata(m_path.c_str(), key, metadata, canUndo);
}

