// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "GraphExecutable.h"
#include "Node.h"

using namespace FabricServices::DFGWrapper;

GraphExecutable::GraphExecutable(FabricCore::DFGBinding binding, std::string path)
: Executable(binding, path)
{
}

GraphExecutable::GraphExecutable(const Executable & other)
: Executable(other)
{
}

GraphExecutable::GraphExecutable(const GraphExecutable & other)
: Executable(other)
{
}

GraphExecutable::~GraphExecutable()
{
}

Node GraphExecutable::addNodeFromPreset(char const * preset)
{
  std::string name = getWrappedCoreBinding().addNodeFromPreset(getPath().c_str(), preset).getCString();
  return Node(getWrappedCoreBinding(), name);
}

Node GraphExecutable::addNodeWithNewGraph(char const * title)
{
  std::string name = getWrappedCoreBinding().addNodeWithNewGraph(getPath().c_str(), title).getCString();
  return Node(getWrappedCoreBinding(), name);
}

Node GraphExecutable::addNodeWithNewFunc(char const * title)
{
  std::string name = getWrappedCoreBinding().addNodeWithNewFunc(getPath().c_str(), title).getCString();
  return Node(getWrappedCoreBinding(), name);
}

Node GraphExecutable::addNodeFromJSON(char const * json)
{
  std::string name = getWrappedCoreBinding().addNodeFromJSON(getPath().c_str(), json).getCString();
  return Node(getWrappedCoreBinding(), name);
}

std::vector<Connection> GraphExecutable::getConnections()
{
  std::vector<Connection> result;

  FabricCore::Variant descVar = FabricCore::Variant::CreateFromJSON(getDesc().c_str());
  const FabricCore::Variant * connectionsVar = descVar.getDictValue("connections");

  std::string prefix = getPath();
  if(prefix.length() > 0)
    prefix += ".";
  
  for(FabricCore::Variant::DictIter connectionIter(*connectionsVar); !connectionIter.isDone(); connectionIter.next())
  {
    std::string srcStr = connectionIter.getKey()->getStringData();
    Port src(getWrappedCoreBinding(), prefix + srcStr);
    
    const FabricCore::Variant * connectedVar = connectionIter.getValue();
    for(uint32_t i=0;i<connectedVar->getArraySize();i++)
    {
      std::string dstStr = connectedVar->getArrayElement(i)->getStringData();
      Port dst(getWrappedCoreBinding(), prefix + dstStr);
      result.push_back(Connection(src, dst));
    }
  }

  return result; 
}
