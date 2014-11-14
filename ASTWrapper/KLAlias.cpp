// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLAlias.h"

using namespace FabricServices::ASTWrapper;

KLAlias::KLAlias(const KLFile* klFile, JSONData data)
: KLCommented(klFile, data)
{
  m_newUserName = getStringDictValue("newUserName");
  m_oldUserName = getStringDictValue("oldUserName");
}

KLAlias::~KLAlias()
{
}

KLDeclType KLAlias::getDeclType() const
{
  return KLDeclType_Alias;
}

bool KLAlias::isOfDeclType(KLDeclType type) const
{
  if(type == getDeclType())
    return true;
  return KLCommented::isOfDeclType(type);
}

const std::string & KLAlias::getNewUserName() const
{
  return m_newUserName;
}

const std::string & KLAlias::getOldUserName() const
{
  return m_oldUserName;
}
