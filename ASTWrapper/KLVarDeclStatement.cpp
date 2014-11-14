// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLVarDeclStatement.h"

#include <vector>
#include <string>

using namespace FabricServices::ASTWrapper;

KLVarDeclStatement::KLVarDeclStatement(const KLFile* klFile, JSONData data, KLStatement * parent)
: KLStatement(klFile, data, parent)
{
  m_baseType = getStringDictValue("baseType");

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

KLDeclType KLVarDeclStatement::getDeclType() const
{
  return KLDeclType_VarDeclStatement;
}

bool KLVarDeclStatement::isOfDeclType(KLDeclType type) const
{
  if(type == KLDeclType_VarDeclStatement)
    return true;
  return KLStatement::isOfDeclType(type);
}

std::string KLVarDeclStatement::getBaseType() const
{
  return m_baseType;
}

uint32_t KLVarDeclStatement::getCount() const
{
  return m_names.size();
}

const std::string & KLVarDeclStatement::getName(uint32_t index) const
{
  return m_names[index];
}

const std::string & KLVarDeclStatement::getArrayModifier(uint32_t index) const
{
  return m_arrayModifiers[index];
}
