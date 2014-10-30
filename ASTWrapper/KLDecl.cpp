// Copyright 2010-2013 Fabric Engine Inc. All rights reserved.

#include "KLDecl.h"

using namespace FabricCore;
using namespace ASTWrapper;

unsigned int gNumKLDeclInstances = 0;

KLDecl::KLDecl(const Variant & data)
{
  m_data = data;
  m_id = gNumKLDeclInstances++;

  if(data.isDict())
  {
    const Variant * owningExtName = data.getDictValue("owningExtName");
    if(owningExtName)
    {
      if(owningExtName)
    }


      if data.has_key('owningExtName'):
        self.__ext = data['owningExtName']
  }
}

const std::string & KLDecl::getID() const
{
  return m_id;
}

Variant KLDecl::getJSON() const
{
  return m_data;
}

const std::string & KLDecl::getExtension() const
{
  return m_extension;
}

const std::string & KLDecl::getKLFile() const
{
  return m_klFile;
}

void KLDecl::setExtension(const std::string & extension)
{
  m_extension = extension;
}

void KLDecl::setKLFile(const std::string & klFile)
{
  m_klFile = klFile;
}

const FabricCore::Variant * KLDecl::getDictValue(const char * key)
{
  if(!m_data.isDict())
    return NULL;

  return m_data.getDictValue(key);
}

const char * KLDecl::getStringDictValue(const char * key)
{
  const Variant * value = data.getDictValue(key);
  if(!value)
    return NULL;

  if(!value->isString())
    return NULL;

  return value->getStringData();
}
