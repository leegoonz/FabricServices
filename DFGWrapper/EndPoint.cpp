// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "EndPoint.h"
#include "Pin.h"
#include "Port.h"

using namespace FabricServices::DFGWrapper;

EndPointPtr EndPoint::Create(
  FabricCore::DFGBinding const &binding,
  FabricCore::DFGExec const &exec,
  char const *execPath,
  char const *endPointPath
  )
{
  if ( strchr( endPointPath, '.' ) != 0 )
    return new Pin(
      binding,
      exec,
      execPath,
      endPointPath
      );
  else
    return new Port(
      binding,
      exec,
      execPath,
      endPointPath
      );
}
