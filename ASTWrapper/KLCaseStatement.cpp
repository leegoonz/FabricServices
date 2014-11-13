// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

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

