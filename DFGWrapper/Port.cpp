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
