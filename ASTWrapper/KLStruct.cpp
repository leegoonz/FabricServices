// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLStruct.h"

using namespace FabricServices::ASTWrapper;

KLStruct::KLStruct(JSONData data)
: KLType(data)
{
  const char * parentStructName = getStringDictValue("parentStructName");
  if(parentStructName)
    m_parentStructName = parentStructName;

  JSONData members = getArrayDictValue("members");
  if(members)
  {
    for(uint32_t i=0;i<members->getArraySize();i++)
    {
      KLMember * member = new KLMember(members->getArrayElement(i));
      m_members.push_back(member);
    }
  }
}

KLStruct::~KLStruct()
{
  // KLMethods are deleted by the KLType destructor
  for(uint32_t i=0;i<m_members.size();i++)
    delete(m_members[i]);
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

uint32_t KLStruct::getMemberCount() const
{
  return m_members.size();
}

const KLMember * KLStruct::getMember(uint32_t index) const
{
  return m_members[index];
}
