// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "GraphExecutable.h"
// #include "Node.h"

using namespace FabricServices::DFGWrapper;

GraphExecutable::GraphExecutable()
{
}

GraphExecutable::GraphExecutable(
  FabricCore::DFGBinding binding,
  FabricCore::DFGExec exec,
  const char * graphPath
  )
: Executable(binding, exec, graphPath)
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
  char const *nodePath = getWrappedCoreExec().addNodeFromPreset(preset);
  return Node(getWrappedCoreBinding(), getWrappedCoreExec(), getGraphPath(), nodePath);
}

Node GraphExecutable::addNodeWithNewGraph(char const * title)
{
  char const *nodePath = getWrappedCoreExec().addNodeWithNewGraph(title);
  return Node(getWrappedCoreBinding(), getWrappedCoreExec(), getGraphPath(), nodePath);
}

Node GraphExecutable::addNodeWithNewFunc(char const * title)
{
  char const *nodePath = getWrappedCoreExec().addNodeWithNewFunc(title);
  return Node(getWrappedCoreBinding(), getWrappedCoreExec(), getGraphPath(), nodePath);
}

Node GraphExecutable::addNodeFromJSON(char const * json)
{
  char const *nodePath = getWrappedCoreExec().addNodeFromJSON(json);
  return Node(getWrappedCoreBinding(), getWrappedCoreExec(), getGraphPath(), nodePath);
}

std::vector<Node> GraphExecutable::getNodes()
{
  std::vector<Node> result;
  for(unsigned int i=0;i<m_exec.getNodeCount();i++)
  {
    result.push_back(
      Node(
        getWrappedCoreBinding(),
        getWrappedCoreExec(),
        getGraphPath(),
        m_exec.getNodeName(i)
      )
    );
  }
  return result; 
}

Node GraphExecutable::getNode(char const * nodePath)
{
  return Node(
    getWrappedCoreBinding(),
    getWrappedCoreExec(),
    getGraphPath(),
    nodePath
  );
}

void GraphExecutable::removeNode(Node node)
{
  getWrappedCoreExec().removeNode(
    node.getNodePath()
  );
}

// std::vector<Connection> GraphExecutable::getConnections()
// {
//   std::vector<Connection> result;

//   FabricCore::Variant descVar = FabricCore::Variant::CreateFromJSON(getDesc().c_str());
//   const FabricCore::Variant * connectionsVar = descVar.getDictValue("connections");

//   std::string prefix = getPath();
//   if(prefix.length() > 0)
//     prefix += ".";
  
//   for(FabricCore::Variant::DictIter connectionIter(*connectionsVar); !connectionIter.isDone(); connectionIter.next())
//   {
//     std::string srcStr = connectionIter.getKey()->getStringData();
//     Port src(getWrappedCoreExec(), prefix + srcStr);
    
//     const FabricCore::Variant * connectedVar = connectionIter.getValue();
//     for(uint32_t i=0;i<connectedVar->getArraySize();i++)
//     {
//       std::string dstStr = connectedVar->getArrayElement(i)->getStringData();
//       Port dst(getWrappedCoreExec(), prefix + dstStr);
//       result.push_back(Connection(src, dst));
//     }
//   }

//   return result; 
// }
