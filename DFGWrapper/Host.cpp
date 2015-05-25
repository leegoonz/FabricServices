// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "Host.h"

using namespace FabricServices::DFGWrapper;

Host::Host()
: m_rootNameSpace(m_host, "")
{
}

Host::Host(FabricCore::Client client)
: m_host(client.getDFGHost())
, m_rootNameSpace(m_host, "")
{
}

Host::Host(const Host & other)
: m_host(other.m_host)
, m_rootNameSpace(m_host, "")
{
}

Host::Host(const FabricCore::DFGHost & other)
: m_host(other)
, m_rootNameSpace(m_host, "")
{
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

void Host::flushUndoRedo()
{
  m_host.flushUndoRedo();
}

NameSpace & Host::getRootNameSpace()
{
  return m_rootNameSpace;
}

void Host::importJSON(char const *parentNameSpace, char const *json, char const *importPathname)
{
  m_host.importJSON(parentNameSpace, json, importPathname);
}

std::string Host::exportJSON(char const * execPath)
{
  return m_host.exportJSON(execPath).getCString();
}

Binding Host::createBindingToNewGraph()
{
  return Binding(m_host.createBindingToNewGraph());
}

Binding Host::createBindingFromJSON(char const * json, uint32_t rtValCount, FabricCore::RTVal const *rtVals)
{
  return Binding(m_host.createBindingFromJSON(json, rtValCount, rtVals));
}

Binding Host::createBindingToPreset(char const * preset, uint32_t rtValCount, FabricCore::RTVal const *rtVals)
{
  return Binding(m_host.createBindingToPreset(preset, rtValCount, rtVals));

}
