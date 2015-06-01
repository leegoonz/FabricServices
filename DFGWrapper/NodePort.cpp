// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "Inst.h"
#include "InstPort.h"
#include "Node.h"
#include "NodePort.h"

using namespace FabricServices::DFGWrapper;

NodePortPtr NodePort::Create(
  FabricCore::DFGBinding const &dfgBinding,
  char const *execPath,
  FabricCore::DFGExec const &dfgExec,
  char const *nodeName,
  char const *portName
  )
{
  return InstPort::Create(
    dfgBinding,
    execPath,
    dfgExec,
    nodeName,
    portName
    );
}

NodePortPtr NodePort::Create(
  FabricCore::DFGBinding const &dfgBinding,
  char const *execPath,
  FabricCore::DFGExec const &dfgExec,
  char const *portPath
  )
{
  return InstPort::Create (
    dfgBinding,
    execPath,
    dfgExec,
    portPath
    );
}

NodePtr NodePort::getNode()
{
  return Inst::Create(
    getDFGBinding(),
    getExecPath(),
    getDFGExec(),
    getNodeName()
    );
}
