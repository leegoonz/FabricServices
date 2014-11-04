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

const char * KLOperator::getKLType() const
{
  return "operator";
}
