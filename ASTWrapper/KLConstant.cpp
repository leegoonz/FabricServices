// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLConstant.h"

using namespace FabricServices::ASTWrapper;

KLConstant::KLConstant(const KLFile* klFile, JSONData data)
: KLCommented(klFile, data)
{
  m_name = getDictValue("constDecl")->getDictValue("name")->getStringData();
  m_type = getDictValue("constDecl")->getDictValue("type")->getStringData();
}

KLConstant::~KLConstant()
{
}

const std::string & KLConstant::getName() const
{
  return m_name;
}

const std::string & KLConstant::getType() const
{
  return m_type;
}
