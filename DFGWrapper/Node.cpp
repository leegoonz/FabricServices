// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "GraphExecutable.h"
#include "Node.h"
#include "Inst.h"
#include "InstPort.h"

using namespace FabricServices::DFGWrapper;

NodePtr Node::Create(
  FabricCore::DFGBinding const &dfgBinding,
  char const *execPath,
  FabricCore::DFGExec const &dfgExec,
  char const *nodeName
  )
{
  return Inst::Create(
    dfgBinding,
    execPath,
    dfgExec,
    nodeName
    );
}

GraphExecutablePtr Node::getOwningGraphExecutable()
{
  return GraphExecutable::Create(
    getDFGBinding(),
    getExecPath(),
    getDFGExec()
    );
}

NodePortList Node::getNodePorts()
{
  NodePortList result;
  unsigned nodePortCount = getDFGExec().getNodePortCount( getNodePath() );
  result.reserve( nodePortCount );
  for(unsigned i=0;i<nodePortCount;i++)
    result.push_back( getNodePort(i) );
  return result;
}

NodePortPtr Node::getNodePort(char const * portName)
{
  return InstPort::Create(
    getDFGBinding(),
    getExecPath(),
    getDFGExec(),
    getNodeName(),
    portName
    );
}

NodePortPtr Node::getNodePort(uint32_t index)
{
  return InstPort::Create(
    getDFGBinding(),
    getExecPath(),
    getDFGExec(),
    getNodeName(),
    getDFGExec().getNodePortName( getNodePath(), index )
    );
}
