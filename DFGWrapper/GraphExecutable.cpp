// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "GraphExecutable.h"

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
