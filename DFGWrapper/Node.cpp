// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "Node.h"

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

std::string Node::getDesc()
{
  return m_binding.getDesc(m_path.c_str()).getCString();
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

std::string Node::exportJSON()
{
  return m_binding.exportJSON(m_path.c_str()).getCString();
}

std::string Node::getMetadata(char const * key)
{
  return m_binding.getMetadata(m_path.c_str(), key);
}

void Node::setMetadata(char const *key, char const * metadata, bool canUndo)
{
  return m_binding.setMetadata(m_path.c_str(), key, metadata, canUndo);
}

std::string Node::getInstanceMetadata(char const * key)
{
  return m_binding.getInstanceMetadata(m_path.c_str(), key);
}

void Node::setInstanceMetadata(char const * key, char const * metadata, bool canUndo)
{
  return m_binding.setInstanceMetadata(m_path.c_str(), key, metadata, canUndo);
}

std::string Node::getImportPathName()
{
  return m_binding.getImportPathname(m_path.c_str());
}

Port Node::addPort(char const *title, FabricCore::DFGPortType portType, char const *dataType)
{
  std::string result = m_binding.addPort(m_path.c_str(), title, portType, dataType).getCString();
  return Port(m_binding, m_path + "." + result);
}
