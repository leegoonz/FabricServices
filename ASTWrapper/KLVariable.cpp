// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLVariable.h"

#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>

using namespace FabricServices::ASTWrapper;

KLVariable::KLVariable(const KLFile* klFile, JSONData data)
: KLCommented(klFile, data)
{
  m_type = getStringDictValue("baseType");
  JSONData varDecls = getArrayDictValue("varDecls");
  if(varDecls)
  {
    for(uint32_t i=0;i<varDecls->getArraySize();i++)
    {
      JSONData varDecl = varDecls->getArrayElement(i);
      m_names.push_back(varDecl->getDictValue("name")->getStringData());
      m_arrayModifiers.push_back(varDecl->getDictValue("arrayModifier")->getStringData());
    }
  }
}

KLVariable::~KLVariable()
{
}

const std::string & KLVariable::getType() const
{
  return m_type;
}

uint32_t KLVariable::getCount() const
{
  return m_names.size();
}

const std::string & KLVariable::getName(uint32_t index) const
{
  return m_names[index];
}

const std::string & KLVariable::getArrayModifier(uint32_t index) const
{
  return m_arrayModifiers[index];
}
