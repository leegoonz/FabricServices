// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "EndPoint.h"

namespace FabricServices { namespace DFGWrapper {

static SharedPtr<EndPoint> EndPoint::Create(
  FabricCore::DFGBinding const &binding,
  char const *execPath,
  char const *endPointPath
  )
{
  if ( strchr( endPointPath, '.' ) != 0 )
    return new Pin(
      binding,
      execPath,
      endPointPath
      );
  else
    return new Port(
      binding,
      execPath,
      endPointPath
      );
}

} }
