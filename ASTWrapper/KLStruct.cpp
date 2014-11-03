// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLStruct.h"

using namespace FabricServices::ASTWrapper;

KLStruct::KLStruct(JSONData data)
: KLType(data)
{
  const char * parentStructName = getStringDictValue("parentStructName");
  if(parentStructName)
    m_parentStructName = parentStructName;
}

KLStruct::~KLStruct()
{
  // KLMethods are deleted by the KLType destructor
}

const char * KLStruct::getKLType() const
{
  return "struct";
}

std::vector<const KLType*> KLStruct::getParents() const
{
  std::vector<const KLType*> parents; 
  if(m_parentStructName.length() > 0)
  {
    const KLType * parent = getKLTypeByName(m_parentStructName.c_str());
    if(parent)
    {
      parents.push_back(parent);
    }
  }
  return parents;
}
