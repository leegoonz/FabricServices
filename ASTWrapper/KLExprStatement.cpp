// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLExprStatement.h"

#include <vector>
#include <string>

using namespace FabricServices::ASTWrapper;

KLExprStatement::KLExprStatement(const KLFile* klFile, JSONData data, KLStatement * parent)
: KLStatement(klFile, data, parent)
{
}

KLDeclType KLExprStatement::getDeclType() const
{
  return KLDeclType_ExprStatement;
}

bool KLExprStatement::isOfDeclType(KLDeclType type) const
{
  if(type == getDeclType())
    return true;
  return KLStatement::isOfDeclType(type);
}

