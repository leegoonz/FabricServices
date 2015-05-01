// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "GraphExecutable.h"
#include <FTL/StrSplit.h>
// #include "Node.h"

using namespace FabricServices::DFGWrapper;

GraphExecutable::GraphExecutable(
  FabricCore::DFGBinding binding,
  FabricCore::DFGExec exec,
  const char * graphPath
  )
: Executable(binding, exec, graphPath)
{
}

GraphExecutablePtr GraphExecutable::Create(
  FabricCore::DFGBinding binding,
  FabricCore::DFGExec exec,
  const char * graphPath
  )
{
  return new GraphExecutable(binding, exec, graphPath);
}

GraphExecutable::~GraphExecutable()
{
}

NodePtr GraphExecutable::addNodeFromPreset(char const * preset)
{
  char const *nodePath = getWrappedCoreExec().addNodeFromPreset(preset);
  return Node::Create(getWrappedCoreBinding(), getWrappedCoreExec(), getGraphPath(), nodePath);
}

NodePtr GraphExecutable::addNodeWithNewGraph(char const * title)
{
  char const *nodePath = getWrappedCoreExec().addNodeWithNewGraph(title);
  return Node::Create(getWrappedCoreBinding(), getWrappedCoreExec(), getGraphPath(), nodePath);
}

NodePtr GraphExecutable::addNodeWithNewFunc(char const * title)
{
  char const *nodePath = getWrappedCoreExec().addNodeWithNewFunc(title);
  return Node::Create(getWrappedCoreBinding(), getWrappedCoreExec(), getGraphPath(), nodePath);
}

NodePtr GraphExecutable::addNodeFromJSON(char const * json)
{
  char const *nodePath = getWrappedCoreExec().addNodeFromJSON(json);
  return Node::Create(getWrappedCoreBinding(), getWrappedCoreExec(), getGraphPath(), nodePath);
}

NodeList GraphExecutable::getNodes()
{
  NodeList result;
  for(unsigned int i=0;i<m_exec.getNodeCount();i++)
  {
    result.push_back(
      Node::Create(
        getWrappedCoreBinding(),
        getWrappedCoreExec(),
        getGraphPath(),
        m_exec.getNodeName(i)
      )
    );
  }
  return result; 
}

NodePtr GraphExecutable::getNode(char const * nodePath)
{
  return Node::Create(
    getWrappedCoreBinding(),
    getWrappedCoreExec(),
    getGraphPath(),
    nodePath
  );
}

void GraphExecutable::removeNode(NodePtr node)
{
  getWrappedCoreExec().removeNode(
    node->getNodePath()
  );
}

std::string GraphExecutable::exportNodesJSON(uint32_t nodeCount, char const * const *nodeNames)
{
  return m_exec.exportNodesJSON(nodeCount, nodeNames).getCString();
}

std::string GraphExecutable::importNodesJSON(char const *nodesJSON)
{
  return m_exec.importNodesJSON(nodesJSON).getCString();
}

char const * GraphExecutable::implodeNodes(char const *desiredName, uint32_t nodeCount, char const * const *nodeNames)
{
  return m_exec.implodeNodes(desiredName, nodeCount, nodeNames);
}

std::vector<std::string> GraphExecutable::explodeNode(char const * nodeName)
{
  std::vector<std::string> result;
  std::string resultStr = m_exec.explodeNode(nodeName).getCString();
  if(resultStr.length() == 0)
    return result;

  FabricCore::Variant resultVar = FabricCore::Variant::CreateFromJSON(resultStr.c_str());
  if(resultVar.isArray())
  {
    for(uint32_t i=0;i<resultVar.getArraySize();i++)
    {
      char const* nodeName = resultVar.getArrayElement(i)->getStringData();
      result.push_back(nodeName);
    }
  }

  return result;
}

ConnectionList GraphExecutable::getConnections()
{
  ConnectionList result;

  FabricCore::Variant descVar = FabricCore::Variant::CreateFromJSON(getDesc().c_str());
  const FabricCore::Variant * connectionsVar = descVar.getDictValue("connections");
  for(FabricCore::Variant::DictIter connectionIter(*connectionsVar); !connectionIter.isDone(); connectionIter.next())
  {
    char const* srcStr = connectionIter.getKey()->getStringData();
    EndPointPtr src = EndPoint::Create(getWrappedCoreBinding(), getWrappedCoreExec(), getExecPath(), srcStr);
    
    const FabricCore::Variant * connectedVar = connectionIter.getValue();
    for(uint32_t i=0;i<connectedVar->getArraySize();i++)
    {
      char const* dstStr = connectedVar->getArrayElement(i)->getStringData();
      EndPointPtr dst = EndPoint::Create(getWrappedCoreBinding(), getWrappedCoreExec(), getExecPath(), dstStr);
      result.push_back(new Connection(src, dst));
    }
  }

  return result; 
}

bool GraphExecutable::canConnectTo(
  char const *srcPath,
  char const *dstPath,
  std::string &failureReason
)
{
  FabricCore::DFGStringResult result = m_exec.canConnectTo(srcPath, dstPath);
  char const *failureReasonData;
  uint32_t failureReasonLength;
  result.getStringDataAndLength( failureReasonData, failureReasonLength );
  failureReason = std::string( failureReasonData, failureReasonLength );
  return failureReason.empty();
}
