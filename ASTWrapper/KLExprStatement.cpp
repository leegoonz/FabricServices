// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLExprStatement.h"

#include <vector>
#include <string>

using namespace FabricServices::ASTWrapper;

KLExprStatement::KLExprStatement(const KLFile* klFile, JSONData data, KLStatement * parent)
: KLStatement(klFile, data, parent)
{
}

