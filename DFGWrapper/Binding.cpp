// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "Binding.h"

using namespace FabricServices::DFGWrapper;

Binding::Binding()
{
  m_binding = FabricCore::DFGBinding();
}

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

bool Binding::isValid() const
{
  return m_binding.isValid();
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

void Binding::setNotificationCallback(FabricCore::DFGNotificationCallback callback, void * userData)
{
  m_binding.setNotificationCallback(callback, userData);
}

bool Binding::canConnect(char const *pathA, char const *pathB)
{
  FabricCore::DFGStringResult result = m_binding.canConnect(pathA, pathB);
  printf("Binding::canConnect pathA '%s'\n", pathA);
  printf("Binding::canConnect pathB '%s'\n", pathB);
  printf("Binding::canConnect '%d' '%s'\n", (result.getCString() == NULL)  ? 1 : 0, result.getCString());
  if(result.getCString() == NULL)
    return false;
  if(std::string(result.getCString()) == "(null)")
    return false;
  return true;
}
