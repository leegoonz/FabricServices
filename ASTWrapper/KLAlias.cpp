// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLAlias.h"

using namespace FabricServices::ASTWrapper;

KLAlias::KLAlias(JSONData data)
: KLDecl(data)
{
  m_newUserName = getStringDictValue("newUserName");
  m_oldUserName = getStringDictValue("oldUserName");
}

KLAlias::~KLAlias()
{
}

const std::string & KLAlias::getNewUserName() const
{
  return m_newUserName;
}

const std::string & KLAlias::getOldUserName() const
{
  return m_oldUserName;
}
