// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "Port.h"
#include "NodePort.h"
#include "ExecPort.h"

using namespace FabricServices::DFGWrapper;

PortPtr Port::Create(
  FabricCore::DFGBinding const &binding,
  FabricCore::DFGExec const &exec,
  char const *execPath,
  char const *endPointPath
  )
{
  if ( strchr( endPointPath, '.' ) != 0 )
    return new NodePort(
      binding,
      exec,
      execPath,
      endPointPath
      );
  else
    return new ExecPort(
      binding,
      exec,
      execPath,
      endPointPath
      );
}
