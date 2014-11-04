// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLCommented.h"

using namespace FabricServices::ASTWrapper;

KLCommented::KLCommented(JSONData data)
: KLDecl(data)
{
  JSONData preComments = getDictValue("preComments");
  if(preComments)
  {
    m_comments = new KLComment(preComments);
  }
  else
  {
    FabricCore::Variant variant = FabricCore::Variant::CreateArray();
    m_comments = new KLComment(&variant);
  }
}

KLCommented::~KLCommented()
{
  delete(m_comments);
}

bool KLCommented::isInternal() const
{
  if(!m_comments)
    return false;
  return m_comments->hasQualifier("internal");
}

void KLCommented::setExtension(const std::string & extension)
{
  KLDecl::setExtension(extension);
  if(m_comments)
    m_comments->setExtension(extension);
}

void KLCommented::setKLFile(const std::string & klFile)
{
  KLDecl::setKLFile(klFile);
  if(m_comments)
    m_comments->setKLFile(klFile);
}

const KLComment * KLCommented::getComments() const
{
  return m_comments;
}
