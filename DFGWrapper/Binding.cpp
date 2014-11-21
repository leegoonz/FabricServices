// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "Binding.h"

using namespace FabricServices::DFGWrapper;

Binding::Binding(FabricCore::DFGBinding binding)
: Node(binding, "")
{
}

Binding::Binding(const Binding & other)
: Node(other)
{
}

Binding::~Binding()
{
}
