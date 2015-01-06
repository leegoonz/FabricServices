// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "KLCStyleLoopStatement.h"

#include <vector>
#include <string>

using namespace FabricServices::ASTWrapper;

KLCStyleLoopStatement::KLCStyleLoopStatement(const KLFile* klFile, JSONData data, KLStatement * parent)
: KLStatement(klFile, data, parent)
{
  JSONData body = getDictValue("body");
  if(body)
    constructChild(body);
}

KLDeclType KLCStyleLoopStatement::getDeclType() const
{
  return KLDeclType_CStyleLoopStatement;
}

bool KLCStyleLoopStatement::isOfDeclType(KLDeclType type) const
{
  if(type == KLDeclType_CStyleLoopStatement)
    return true;
  return KLStatement::isOfDeclType(type);
}
