// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "GraphNode.h"

using namespace FabricServices::DFGWrapper;

GraphNode::GraphNode(FabricCore::DFGBinding binding, std::string path)
: Node(binding, path)
{
}

GraphNode::GraphNode(const Node & other)
: Node(other)
{
}

GraphNode::GraphNode(const GraphNode & other)
: Node(other)
{
}

GraphNode::~GraphNode()
{
}
