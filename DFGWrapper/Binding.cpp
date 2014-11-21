// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "Binding.h"

using namespace FabricServices::DFGWrapper;

Binding::Binding(FabricCore::DFGBinding binding)
{
  m_binding = binding;
}

Binding::Binding(const Binding & other)
{
  m_binding = other.m_binding;
}

Binding::~Binding()
{
}

FabricCore::DFGBinding Binding::getWrappedCoreBinding() const
{
  return m_binding;
}

FabricCore::RTVal Binding::getArgValue(char const *name)
{
  return m_binding.getArgValue(name);
}

void Binding::setArgValue(char const *name, FabricCore::RTVal value)
{
  m_binding.setArgValue(name, value);
}

GraphExecutable Binding::getGraph()
{
  return GraphExecutable(m_binding, "");
}

void Binding::execute()
{
  m_binding.execute();
}
