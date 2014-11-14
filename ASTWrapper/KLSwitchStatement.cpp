// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLSwitchStatement.h"

#include <vector>
#include <string>

using namespace FabricServices::ASTWrapper;

KLSwitchStatement::KLSwitchStatement(const KLFile* klFile, JSONData data, KLStatement * parent)
: KLStatement(klFile, data, parent)
{
  JSONData cases = getArrayDictValue("cases");
  if(cases)
  {
    for(uint32_t i=0;i<cases->getArraySize();i++)
      constructChild(cases->getArrayElement(i));
  }
}

KLDeclType KLSwitchStatement::getDeclType() const
{
  return KLDeclType_SwitchStatement;
}

bool KLSwitchStatement::isOfDeclType(KLDeclType type) const
{
  if(type == getDeclType())
    return true;
  return KLStatement::isOfDeclType(type);
}
