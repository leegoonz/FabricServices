// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLComment.h"

using namespace FabricServices::ASTWrapper;

KLComment::KLComment(JSONData data)
: KLDecl(data)
{
}

bool KLComment::isInternal() const
{
  return true;
}
