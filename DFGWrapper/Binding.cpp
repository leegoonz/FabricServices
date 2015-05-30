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

void Binding::flush()
{
  m_binding.flush();
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

ExecutablePtr Binding::getExecutable()
{
  return Executable::Create(
    m_binding,
    "",
    m_binding.getExec()
    );
}

void Binding::execute()
{
  m_binding.execute();
}

void Binding::setNotificationCallback(FabricCore::DFGNotificationCallback callback, void * userData)
{
  m_binding.setNotificationCallback(callback, userData);
}

std::string Binding::exportJSON()
{
  return m_binding.exportJSON().getCString();
}
