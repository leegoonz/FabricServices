// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLOperator.h"

using namespace FabricServices::ASTWrapper;

KLOperator::KLOperator(const KLFile* klFile, JSONData data)
: KLFunction(klFile, data)
{
}

KLOperator::~KLOperator()
{
}

KLDeclType KLOperator::getDeclType() const
{
  return KLDeclType_Operator;
}

bool KLOperator::isOfDeclType(KLDeclType type) const
{
  if(type == KLDeclType_Operator)
    return true;
  return KLFunction::isOfDeclType(type);
}

const char * KLOperator::getKLType() const
{
  return "operator";
}
