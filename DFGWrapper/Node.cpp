// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "Node.h"

using namespace FabricServices::DFGWrapper;

Node::Node(FabricCore::DFGBinding binding, std::string path)
{
  m_binding = binding;
  m_path = path;
}

Node::Node(const Node & other)
{
  m_binding = other.m_binding;
  m_path = other.m_path;
}

Node::~Node()
{
}

FabricCore::DFGBinding Node::getWrappedCoreBinding() const
{
  return m_binding;
}

