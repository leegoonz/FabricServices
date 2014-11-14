// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLParameter.h"

#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>

using namespace FabricServices::ASTWrapper;

KLParameter::KLParameter(const KLFile* klFile, JSONData data)
: KLDecl(klFile, data)
{
  m_usage = getStringDictValue("usage");
  m_name = getStringDictValue("name");
  m_type = getStringDictValue("type");
}

KLParameter::~KLParameter()
{
}

KLDeclType KLParameter::getDeclType() const
{
  return KLDeclType_Parameter;
}

bool KLParameter::isOfDeclType(KLDeclType type) const
{
  return type == getDeclType();
}

const std::string & KLParameter::getUsage() const
{
  return m_usage;
}

const std::string & KLParameter::getName() const
{
  return m_name;
}

const std::string & KLParameter::getType() const
{
  return m_type;
}

std::string KLParameter::getTypeNoArray() const
{
  std::vector<std::string> parts;
  boost::split(parts, m_type, boost::is_any_of("["));
  std::string type = parts[0];
  if(type.substr(type.length()-2, 2) == "<>")
    type = type.substr(0, type.length()-2);
  return type;
}

std::string KLParameter::getTypeArraySuffix() const
{
  if(m_type.substr(m_type.length()-2, 2) == "<>")
    return "<>";
  if(m_type.substr(m_type.length()-1, 1) == "]")
  {
    std::vector<std::string> parts;
    boost::split(parts, m_type, boost::is_any_of("["));
    return "[" + parts[1];
  }
  return "";
}

