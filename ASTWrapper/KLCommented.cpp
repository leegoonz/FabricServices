// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "KLCommented.h"

using namespace FabricServices::ASTWrapper;

KLCommented::KLCommented(const KLFile* klFile, JSONData data)
: KLDecl(klFile, data)
{
  JSONData preComments = getDictValue("preComments");
  if(preComments)
  {
    m_comments = new KLComment(klFile, preComments);
  }
  else
  {
    FabricCore::Variant variant = FabricCore::Variant::CreateArray();
    m_comments = new KLComment(klFile, &variant);
  }
}

KLCommented::~KLCommented()
{
  delete(m_comments);
}

KLDeclType KLCommented::getDeclType() const
{
  return KLDeclType_Commented;
}

bool KLCommented::isOfDeclType(KLDeclType type) const
{
  return type == KLDeclType_Commented;
}

bool KLCommented::isInternal() const
{
  if(!m_comments)
    return false;
  return m_comments->hasQualifier("internal");
}

const KLComment * KLCommented::getComments() const
{
  return m_comments;
}
