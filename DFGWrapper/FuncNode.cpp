// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "FuncNode.h"

using namespace FabricServices::DFGWrapper;

FuncNode::FuncNode(FabricCore::DFGBinding binding, std::string path)
: Node(binding, path)
{
}

FuncNode::FuncNode(const Node & other)
: Node(other)
{
}

FuncNode::FuncNode(const FuncNode & other)
: Node(other)
{
}

FuncNode::~FuncNode()
{
}
