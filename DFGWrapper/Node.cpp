// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

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

bool Node::isValid() const
{
  return m_binding.isValid();
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

std::vector<std::string> Node::getDataTypes()
{
 std::vector<std::string> result;

  FabricCore::Variant descVar = FabricCore::Variant::CreateFromJSON(getDesc().c_str());
  const FabricCore::Variant * typesVar = descVar.getDictValue("types");
  for(uint32_t i=0;i<typesVar->getArraySize();i++)
  {
    const FabricCore::Variant * typeVar = typesVar->getArrayElement(i);
    if(typeVar->isString())
      result.push_back(typeVar->getStringData());
    else
      result.push_back("");
  }
  return result;
}

std::string Node::getMetadata(char const * key)
{
  return m_binding.getInstanceMetadata(m_path.c_str(), key);
}

void Node::setMetadata(char const *key, char const * metadata, bool canUndo)
{
  return m_binding.setInstanceMetadata(m_path.c_str(), key, metadata, canUndo);
}

std::vector<Pin> Node::getPins()
{
  std::vector<Pin> result;

  FabricCore::Variant descVar = FabricCore::Variant::CreateFromJSON(getDesc().c_str());
  const FabricCore::Variant * pinsVar = descVar.getDictValue("pins");
  for(uint32_t i=0;i<pinsVar->getArraySize();i++)
  {
    const FabricCore::Variant * pinVar = pinsVar->getArrayElement(i);
    const FabricCore::Variant * nameVar = pinVar->getDictValue("name");
    std::string nameStr = nameVar->getStringData();
    result.push_back(Pin(getWrappedCoreBinding(), getPath() + "." + nameStr));
  }
  return result;
}

Pin Node::getPin(char const * name)
{
  std::string prefix = getPath();
  if(prefix.length() > 0)
    prefix += ".";
  return Pin(m_binding, prefix + name);
}

Pin Node::getPin(uint32_t index)
{
  return getPins()[index];
}