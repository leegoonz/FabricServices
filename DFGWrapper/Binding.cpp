// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "Binding.h"

using namespace FabricServices::DFGWrapper;

Binding::Binding(FabricCore::DFGBinding binding)
: GraphNode(binding, "")
{
}

Binding::Binding(const Binding & other)
: GraphNode(other)
{
}

Binding::~Binding()
{
}

FabricCore::RTVal Binding::getArgValue(char const *name)
{
  return getWrappedCoreBinding().getArgValue(name);
}

void Binding::setArgValue(char const *name, FabricCore::RTVal value)
{
  getWrappedCoreBinding().setArgValue(name, value);
}

void Binding::execute()
{
  getWrappedCoreBinding().execute();
}
