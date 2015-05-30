// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "ExecPort.h"
#include "Inst.h"
#include "InstPort.h"

using namespace FabricServices::DFGWrapper;

InstPtr InstPort::getInst()
{
  return Inst::Create(
    getDFGBinding(),
    getExecPath(),
    getDFGExec(),
    getNodeName()
    );
}

ExecPortPtr InstPort::getExecPort()
{
  return ExecPort::Create(
    getDFGBinding(),
    getExecPath(),
    getDFGExec().getSubExec( getNodeName() ),
    getPortName()
    );
}
