// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "Port.h"

using namespace FabricServices::DFGWrapper;

Port::Port(FabricCore::DFGBinding binding, std::string path)
{
  m_binding = binding;
  m_path = path;
}

Port::Port(const Port & other)
{
  m_binding = other.m_binding;
  m_path = other.m_path;
}

Port::~Port()
{
}

FabricCore::DFGBinding Port::getWrappedCoreBinding() const
{
  return m_binding;
}

std::string Port::getPath() const
{
  return m_path;
}

std::string Port::getTitle() const
{
  if(m_path.length() == 0)
    return "";
  int pos = m_path.rfind('.');
  if(pos == std::string::npos)
    return m_path;
  return m_path.substr(pos+1, m_path.length());
}

void Port::connect(const Port & other)
{
  m_binding.connect(m_path.c_str(), other.m_path.c_str());
}

void Port::disconnect(const Port & other)
{
  m_binding.disconnect(m_path.c_str(), other.m_path.c_str());
}

void Port::addDebugPin()
{
  m_binding.addDebugPin(m_path.c_str());
}

FabricCore::RTVal Port::getDebugPinValue()
{
  return m_binding.getDebugPinValue(m_path.c_str());
}

void Port::removeDebugPin()
{
  m_binding.removeDebugPin(m_path.c_str());
}

void Port::setPinDefaultValue(FabricCore::RTVal defaultValue)
{
  m_binding.setPinDefaultValue(m_path.c_str(), defaultValue);
}
