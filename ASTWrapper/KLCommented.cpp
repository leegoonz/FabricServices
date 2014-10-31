// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLCommented.h"

using namespace FabricServices::ASTWrapper;

KLCommented::KLCommented(JSONData data)
: KLDecl(data)
{
  JSONData preComments = getDictValue("preComments");
  if(preComments)
    m_comments = new KLComment(preComments);
  else
    m_comments = NULL;
}

const KLComment * KLCommented::getComments() const
{
  return m_comments;
}
