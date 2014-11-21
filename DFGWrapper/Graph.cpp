// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "Graph.h"

using namespace FabricServices::DFGWrapper;

Graph::Graph(FabricCore::DFGHost host, std::string path)
: Object(host, path)
{
}

Graph::Graph(const Graph & other)
: Object(other)
{
}

Graph::~Graph()
{
}
