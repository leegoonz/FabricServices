// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "GraphExecutable.h"
#include "Node.h"

using namespace FabricServices::DFGWrapper;

GraphExecutable::GraphExecutable()
{
}

GraphExecutable::GraphExecutable(
  FabricCore::DFGBinding binding,
  char const *graphPath
  )
: Executable(binding, graphPath)
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
  char const *nodePath = getWrappedCoreBinding().addNodeFromPreset(getGraphPath(), preset);
  return Node(getWrappedCoreBinding(), getGraphPath(), nodePath);
}

Node GraphExecutable::addNodeWithNewGraph(char const * title)
{
  char const *nodePath = getWrappedCoreBinding().addNodeWithNewGraph(getGraphPath(), title);
  return Node(getWrappedCoreBinding(), getGraphPath(), nodePath);
}

Node GraphExecutable::addNodeWithNewFunc(char const * title)
{
  char const *nodePath = getWrappedCoreBinding().addNodeWithNewFunc(getGraphPath(), title);
  return Node(getWrappedCoreBinding(), getGraphPath(), nodePath);
}

Node GraphExecutable::addNodeFromJSON(char const * json)
{
  char const *nodePath = getWrappedCoreBinding().addNodeFromJSON(getGraphPath(), json);
  return Node(getWrappedCoreBinding(), getGraphPath(), nodePath);
}

std::vector<Node> GraphExecutable::getNodes()
{
  std::vector<Node> result;

  FabricCore::Variant descVar = FabricCore::Variant::CreateFromJSON(getDesc().c_str());
  const FabricCore::Variant * nodesVar = descVar.getDictValue("nodes");

  for(uint32_t i=0;i<nodesVar->getArraySize();i++)
  {
    const FabricCore::Variant * nodeVar = nodesVar->getArrayElement(i);
    const FabricCore::Variant * nameVar = nodeVar->getDictValue("name");
    result.push_back(
      Node(
        getWrappedCoreBinding(),
        getGraphPath(),
        nameVar->getStringData()
        )
      );
  }

  return result; 
}

Node GraphExecutable::getNode(char const * nodePath)
{
  return Node(
    getWrappedCoreBinding(),
    getGraphPath(),
    nodePath
    );
}

void GraphExecutable::removeNode(Node node)
{
  getWrappedCoreBinding().removeNode(
    getGraphPath(),
    node.getNodePath()
    );
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
