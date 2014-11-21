// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "FuncExecutable.h"

using namespace FabricServices::DFGWrapper;

FuncExecutable::FuncExecutable(FabricCore::DFGBinding binding, std::string path)
: Executable(binding, path)
{
}

FuncExecutable::FuncExecutable(const Executable & other)
: Executable(other)
{
}

FuncExecutable::FuncExecutable(const FuncExecutable & other)
: Executable(other)
{
}

FuncExecutable::~FuncExecutable()
{
}
