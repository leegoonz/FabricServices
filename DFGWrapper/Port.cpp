// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "InstPort.h"
#include "ExecPort.h"

using namespace FabricServices::DFGWrapper;

PortPtr Port::Create(
  FabricCore::DFGBinding const &dfgBinding,
  char const *execPath,
  FabricCore::DFGExec const &dfgExec,
  char const *portPath
  )
{
  char const *dot = strchr( portPath, '.' );
  if ( !!dot )
  {
    unsigned nodeSize = dot - portPath;
    char *nodeName = static_cast<char *>( alloca( nodeSize + 1 ) );
    memcpy( nodeName, portPath, nodeSize );
    nodeName[nodeSize] = 0;

    char const *portName = dot + 1;
    return InstPort::Create(
      dfgBinding,
      execPath,
      dfgExec,
      nodeName,
      portName
      );
  }
  else
  {
    return ExecPort::Create(
      dfgBinding,
      execPath,
      dfgExec,
      portPath
      );
  }
}
