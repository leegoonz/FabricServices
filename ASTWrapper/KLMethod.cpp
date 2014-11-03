// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLMethod.h"

using namespace FabricServices::ASTWrapper;

KLMethod::KLMethod(JSONData data, const std::string & thisType)
: KLFunction(data)
{
  const char * dictThisType = getStringDictValue("thisType");
  if(dictThisType)
    m_thisType = dictThisType;
  else
    m_thisType = thisType;

  const char * thisUsage = getStringDictValue("thisUsage");
  if(thisUsage)
    m_thisUsage = thisUsage;
  else
    m_thisUsage = "in";
}

KLMethod::~KLMethod()
{
}

const std::string & KLMethod::getThisType() const
{
  return m_thisType;
}

const std::string & KLMethod::getThisUsage() const
{
  return m_thisUsage;
}

bool KLMethod::isMethod() const
{
  return true;
}

std::string KLMethod::getPrefix() const
{
  // filter out constructors / destructors
  if(m_thisType == getName() || "~" + m_thisType == getName())
    return "";

  return m_thisType + ".";
}

std::string KLMethod::getSuffix() const
{
  if(m_thisUsage == "in")
    return "?";
  return "!";
}

const KLComment * KLMethod::getComments() const
{
  const KLComment * comments = KLFunction::getComments();
  if(comments)
    return comments;

  // todo... check the parents.... ideally walk up to the interface

  return NULL;
}

