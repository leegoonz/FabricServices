// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLConditionalStatement.h"

#include <vector>
#include <string>

using namespace FabricServices::ASTWrapper;

KLConditionalStatement::KLConditionalStatement(const KLFile* klFile, JSONData data, KLStatement * parent)
: KLStatement(klFile, data, parent)
{
  JSONData trueStatement = getDictValue("trueStatement");
  if(trueStatement)
    constructChild(trueStatement);
  JSONData falseStatement = getDictValue("falseStatement");
  if(falseStatement)
    constructChild(falseStatement);
}

const KLStatement * KLConditionalStatement::getTrueStatement() const
{
  if(getChildCount() > 0)
    return getChild(0);
  return NULL;
}

const KLStatement * KLConditionalStatement::getFalseStatement() const
{
  if(getChildCount() > 1)
    return getChild(1);
  return NULL;
}

