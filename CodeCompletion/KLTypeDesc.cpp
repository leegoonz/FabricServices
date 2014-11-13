// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLTypeDesc.h"

using namespace FabricServices::CodeCompletion;

KLTypeDesc::KLTypeDesc(const std::string & type)
{
  m_type = type;

  int pos = m_type.find('[');
  if(pos != std::string::npos)
  {
    m_arrayModifier = m_type.substr(pos, 10000);
    m_type = m_type.substr(0, pos);
  }
  else
  {
    pos = m_type.find('<');
    if(pos != std::string::npos)
    {
      if(m_type[pos+1] == '>')
      {
        m_arrayModifier = m_type.substr(pos, 2);
        m_type = m_type.substr(0, pos);
      }
    }
  }  
}

KLTypeDesc::KLTypeDesc(const std::string & type, const std::string & arrayModifier)
{
  m_type = type;
  m_arrayModifier = arrayModifier;
}

KLTypeDesc::~KLTypeDesc()
{
}

const std::string & KLTypeDesc::getType() const
{
  return m_type;
}

std::string KLTypeDesc::getBaseType() const
{
  if(!isRef())
    return getType();
  return m_type.substr(4, m_type.length() - 6);
}

const std::string & KLTypeDesc::getArrayModifier() const
{
  return m_arrayModifier;
}

bool KLTypeDesc::isArray() const
{
  return m_arrayModifier == "[]" || m_arrayModifier == "<>";
}

bool KLTypeDesc::isDict() const
{
  if(m_arrayModifier == "")
    return false;
  return !isArray() && m_arrayModifier[0] == '[';
}

bool KLTypeDesc::isRef() const
{
  return m_type.substr(0, 4) == "Ref<";
}

