// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "Port.h"

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

SharedPtr<DFGEndPoint> EndPoint::getSources()
{
  FabricCore::Variant descVar =
    FabricCore::Variant::CreateFromJSON( getDesc().c_str() );
  const FabricCore::Variant * connectionsVar = descVar.getDictValue("connections");
  if(connectionsVar)
  {
    for(FabricCore::Variant::DictIter connectionIter(*connectionsVar); !connectionIter.isDone(); connectionIter.next())
    {
      char const *name = connectionIter.getKey()->getStringData();
      if ( strcmp( name, "src" ) != 0 )
        continue;
      const FabricCore::Variant * sourceVar = connectionIter.getValue();
      if(sourceVar->isString())
      {
        return EndPoint::Create(
          getWrappedCoreBinding(),
          getExecPath(),

      }
    }
  }
  return SharedPtr<DFGEndPoint>;
}

std::vector<std::string> EndPoint::getDestinations()
{
  std::vector<std::string> result;
  FabricCore::Variant descVar = FabricCore::Variant::CreateFromJSON(getDesc().c_str());
  const FabricCore::Variant * connectionsVar = descVar.getDictValue("dsts");
  if(connectionsVar)
  {
    for(unsigned int i=0;i<connectionsVar->getArraySize();i++)
    {
      const FabricCore::Variant * connectionVar = connectionsVar->getArrayElement(i);
      if(connectionVar->isString())
      {
        std::string name = connectionVar->getStringData();
        if(name != getName())
          result.push_back(name);
      }
    }
  }
  return result;
}

} }
