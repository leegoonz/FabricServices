// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "Host.h"

using namespace FabricServices::DFGWrapper;

Host::Host(FabricCore::Client client)
{
  m_host = client.getDFGHost();
}

Host::Host(const Host & other)
{
  m_host = other.m_host;
}

Host::~Host()
{
}

FabricCore::DFGHost Host::getWrappedCoreHost() const
{
  return m_host;
}

bool Host::maybeUndo()
{
  return m_host.maybeUndo();
}

bool Host::maybeRedo()
{
  return m_host.maybeRedo();
}

NameSpace Host::getRootNameSpace() const
{
  return NameSpace(m_host, "");
}

Binding Host::createBindingToNewGraph()
{
  return Binding(m_host.createBindingToNewGraph());
}
