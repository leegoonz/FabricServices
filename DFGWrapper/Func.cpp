// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "Func.h"

using namespace FabricServices::DFGWrapper;

Func::Func(FabricCore::DFGHost host, std::string path)
: Object(host, path)
{
}

Func::Func(const Func & other)
: Object(other)
{
}

Func::~Func()
{
}
