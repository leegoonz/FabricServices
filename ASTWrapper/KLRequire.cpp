// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLRequire.h"

using namespace FabricServices::ASTWrapper;

KLRequire::KLRequire(JSONData data)
: KLCommented(data)
{
  JSONData require = getArrayDictValue("requires")->getArrayElement(0);
  m_requiredExtension = require->getDictValue("name")->getStringData();
  m_versionRange = require->getDictValue("versionRange")->getStringData();
}

KLRequire::~KLRequire()
{
}

const std::string & KLRequire::getRequiredExtension() const
{
  return m_requiredExtension;
}

const std::string & KLRequire::getVersionRange() const
{
  return m_versionRange;
}

