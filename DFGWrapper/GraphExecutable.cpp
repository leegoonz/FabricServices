// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "GraphExecutable.h"
#include "Inst.h"

using namespace FabricServices::DFGWrapper;

InstPtr GraphExecutable::addInstFromPreset(char const * preset)
{
  return Inst::Create(
    getDFGBinding(),
    getExecPath(),
    getDFGExec(),
    getDFGExec().addInstFromPreset( preset )
    );
}

InstPtr GraphExecutable::addInstWithNewGraph(char const * title)
{
  return Inst::Create(
    getDFGBinding(),
    getExecPath(),
    getDFGExec(),
    getDFGExec().addInstWithNewGraph(title)
    );
}

InstPtr GraphExecutable::addInstWithNewFunc(char const * title)
{
  return Inst::Create(
    getDFGBinding(),
    getExecPath(),
    getDFGExec(),
    getDFGExec().addInstWithNewFunc(title)
    );
}

InstPtr GraphExecutable::addInstFromJSON(char const * json)
{
  return Inst::Create(
    getDFGBinding(),
    getExecPath(),
    getDFGExec(),
    getDFGExec().addInstFromJSON(json)
    );
}

NodeList GraphExecutable::getNodes()
{
  NodeList result;
  unsigned nodeCount = getDFGExec().getNodeCount();
  result.reserve( nodeCount );
  for(unsigned int i=0;i<nodeCount;i++)
    result.push_back( getNode(i) );
  return result; 
}

NodePtr GraphExecutable::getNode(char const * nodePath)
{
  return Inst::Create(
    getDFGBinding(),
    getExecPath(),
    getDFGExec(),
    nodePath
    );
}

NodePtr GraphExecutable::getNode(uint32_t index)
{
  return Inst::Create(
    getDFGBinding(),
    getExecPath(),
    getDFGExec(),
    getDFGExec().getNodeName(index)
    );
}

void GraphExecutable::removeNode(NodePtr node)
{
  getDFGExec().removeNode( node->getNodePath() );
}

std::string GraphExecutable::exportNodesJSON(uint32_t nodeCount, char const * const *nodeNames)
{
  return getDFGExec().exportNodesJSON(nodeCount, nodeNames).getCString();
}

std::string GraphExecutable::importNodesJSON(char const *nodesJSON)
{
  return getDFGExec().importNodesJSON(nodesJSON).getCString();
}

char const * GraphExecutable::implodeNodes(char const *desiredName, uint32_t nodeCount, char const * const *nodeNames)
{
  return getDFGExec().implodeNodes(desiredName, nodeCount, nodeNames);
}

std::vector<std::string> GraphExecutable::explodeNode(char const * nodeName)
{
  std::vector<std::string> result;
  std::string resultStr = getDFGExec().explodeNode(nodeName).getCString();
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

  FabricCore::Variant descVar =
    FabricCore::Variant::CreateFromJSON(getDesc().c_str());
  const FabricCore::Variant * connectionsVar =
    descVar.getDictValue("connections");
  for ( FabricCore::Variant::DictIter connectionIter(*connectionsVar);
    !connectionIter.isDone(); connectionIter.next() )
  {
    char const* srcStr = connectionIter.getKey()->getStringData();
    PortPtr src = Port::Create(
      getDFGBinding(),
      getExecPath(),
      getDFGExec(),
      srcStr
      );
    
    const FabricCore::Variant * connectedVar = connectionIter.getValue();
    for(uint32_t i=0;i<connectedVar->getArraySize();i++)
    {
      char const* dstStr = connectedVar->getArrayElement(i)->getStringData();
      PortPtr dst = Port::Create(
        getDFGBinding(),
        getExecPath(),
        getDFGExec(),
        dstStr
        );
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
  FabricCore::DFGStringResult result =
    getDFGExec().canConnectTo(srcPath, dstPath);
  char const *failureReasonData;
  uint32_t failureReasonLength;
  result.getStringDataAndLength( failureReasonData, failureReasonLength );
  failureReason = std::string( failureReasonData, failureReasonLength );
  return failureReason.empty();
}
