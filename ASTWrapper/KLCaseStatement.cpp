// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "KLCaseStatement.h"

#include <vector>
#include <string>

using namespace FabricServices::ASTWrapper;

KLCaseStatement::KLCaseStatement(const KLFile* klFile, JSONData data, KLStatement * parent)
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

KLDeclType KLCaseStatement::getDeclType() const
{
  return KLDeclType_CaseStatement;
}

bool KLCaseStatement::isOfDeclType(KLDeclType type) const
{
  if(type == KLDeclType_CaseStatement)
    return true;
  return KLStatement::isOfDeclType(type);
}
