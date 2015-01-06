// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "Connection.h"

using namespace FabricServices::DFGWrapper;

Connection::Connection(Port src, Port dst)
: m_src(src)
, m_dst(dst)
{
}

Connection::Connection(const Connection & other)
: m_src(other.m_src)
, m_dst(other.m_dst)
{
}

Connection::~Connection()
{
}

bool Connection::isValid() const
{
  return m_src.isValid() && m_dst.isValid();
}

Port Connection::getSrc() const
{
  return m_src;
}

Port Connection::getDst() const
{
  return m_dst;
}
