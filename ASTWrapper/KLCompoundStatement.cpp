// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLCompoundStatement.h"

#include <vector>
#include <string>

using namespace FabricServices::ASTWrapper;

KLCompoundStatement::KLCompoundStatement(const KLFile* klFile, JSONData data, KLStatement * parent)
: KLStatement(klFile, data, parent)
{
  JSONData statements = getArrayDictValue("statements");
  if(statements)
  {
    for(uint32_t i=0;i<statements->getArraySize();i++)
    {
      constructChild(statements->getArrayElement(i));
    }
  }
}

KLDeclType KLCompoundStatement::getDeclType() const
{
  return KLDeclType_CompoundStatement;
}

bool KLCompoundStatement::isOfDeclType(KLDeclType type) const
{
  if(type == getDeclType())
    return true;
  return KLStatement::isOfDeclType(type);
}
