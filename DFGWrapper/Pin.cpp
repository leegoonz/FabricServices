// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "Pin.h"

using namespace FabricServices::DFGWrapper;

Pin::Pin(FabricCore::DFGBinding binding, std::string path)
: Port(binding, path)
{
}

Pin::Pin(const Pin & other)
: Port(other)
{
  m_pinType = other.m_pinType;
}

Pin::~Pin()
{
}

FabricCore::DFGPortType Pin::getPinType()
{
  if(m_pinType.length() == 0)
  {
    FabricCore::Variant descVar = FabricCore::Variant::CreateFromJSON(getDesc().c_str());
    const FabricCore::Variant * typeVar = descVar.getDictValue("endPointType");
    m_pinType = typeVar->getStringData();
  }
  if(m_pinType == "In")
    return FabricCore::DFGPortType_In;
  if(m_pinType == "Out")
    return FabricCore::DFGPortType_Out;
  return FabricCore::DFGPortType_IO;
}

std::string Pin::getDesc()
{
  return getWrappedCoreBinding().getInstanceDesc(getPath().c_str()).getCString();
}

Port Pin::getPort()
{
  return Port(getWrappedCoreBinding(), getPath());
}

void Pin::addDebugPin()
{
  getWrappedCoreBinding().addDebugPin(getPath().c_str());
}

FabricCore::RTVal Pin::getDebugPinValue()
{
  return getWrappedCoreBinding().getDebugPinValue(getPath().c_str());
}

void Pin::removeDebugPin()
{
  getWrappedCoreBinding().removeDebugPin(getPath().c_str());
}

void Pin::setPinDefaultValue(FabricCore::RTVal defaultValue)
{
  getWrappedCoreBinding().setPinDefaultValue(getPath().c_str(), defaultValue);
}
