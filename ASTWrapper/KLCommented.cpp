// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLCommented.h"

using namespace FabricCore;
using namespace ASTWrapper;

KLCommented::KLCommented(const Variant * data)
: KLDecl(data)
{
  const Variant * preComments = getDictValue("preComments");
  if(preComments)
    m_comments = KLComment::Ptr(new KLComment(preComments));
}

KLComment::Ptr KLCommented::getComments() const
{
  return m_comments;
}
