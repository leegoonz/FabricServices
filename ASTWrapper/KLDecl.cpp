// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLDecl.h"

using namespace FabricServices::ASTWrapper;

// todo: add a mutex around this
unsigned int gNumKLDeclInstances = 0;

KLDecl::KLDecl(JSONData data)
{
  m_data = data;
  m_id = gNumKLDeclInstances++;

  const char * owningExtName = getStringDictValue("owningExtName");
  if(owningExtName)
    m_extension = owningExtName;      
}

unsigned int KLDecl::getID() const
{
  return m_id;
}

JSONData KLDecl::getJSON() const
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

JSONData KLDecl::getDictValue(const char * key)
{
  if(!m_data->isDict())
    return NULL;

  return m_data->getDictValue(key);
}

const char * KLDecl::getStringDictValue(const char * key)
{
  JSONData value = getDictValue(key);
  if(!value)
    return NULL;

  if(!value->isString())
    return NULL;

  return value->getStringData();
}
