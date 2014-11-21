// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "GraphExecutable.h"
#include "Node.h"

using namespace FabricServices::DFGWrapper;

GraphExecutable::GraphExecutable(FabricCore::DFGBinding binding, std::string path)
: Executable(binding, path)
{
}

GraphExecutable::GraphExecutable(const Executable & other)
: Executable(other)
{
}

GraphExecutable::GraphExecutable(const GraphExecutable & other)
: Executable(other)
{
}

GraphExecutable::~GraphExecutable()
{
}

Node GraphExecutable::addNodeFromPreset(char const * preset)
{
  std::string name = getWrappedCoreBinding().addNodeFromPreset(getPath().c_str(), preset).getCString();
  return Node(getWrappedCoreBinding(), name);
}

Node GraphExecutable::addNodeWithNewGraph(char const * title)
{
  std::string name = getWrappedCoreBinding().addNodeWithNewGraph(getPath().c_str(), title).getCString();
  return Node(getWrappedCoreBinding(), name);
}

Node GraphExecutable::addNodeWithNewFunc(char const * title)
{
  std::string name = getWrappedCoreBinding().addNodeWithNewFunc(getPath().c_str(), title).getCString();
  return Node(getWrappedCoreBinding(), name);
}

Node GraphExecutable::addNodeFromJSON(char const * json)
{
  std::string name = getWrappedCoreBinding().addNodeFromJSON(getPath().c_str(), json).getCString();
  return Node(getWrappedCoreBinding(), name);
}
