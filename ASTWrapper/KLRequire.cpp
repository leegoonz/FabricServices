// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLRequire.h"

using namespace FabricServices::ASTWrapper;

KLRequire::KLRequire(JSONData data)
: KLDecl(data)
{
  JSONData require = getArrayDictValue("requires")->getArrayElement(0);
  m_requiredExtension = require->getDictValue("name")->getStringData();
  // todo: versioning info
}

KLRequire::~KLRequire()
{
}

const std::string & KLRequire::getRequiredExtension() const
{
  return m_requiredExtension;
}

