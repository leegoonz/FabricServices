// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLDecl.h"

#include <map>

#include <boost/thread/locks.hpp>
#include <boost/thread/shared_mutex.hpp>
typedef boost::shared_mutex Lock;
typedef boost::unique_lock< Lock >  WriteLock;
typedef boost::shared_lock< Lock >  ReadLock;
Lock gKLDeclLock;

using namespace FabricServices::ASTWrapper;

uint32_t gNumKLDeclInstances = 0;
std::map<uint32_t, KLDecl*> s_allDecls;

KLDecl::KLDecl(JSONData data)
{
  WriteLock w_lock(gKLDeclLock);

  m_data = data;
  m_id = gNumKLDeclInstances++;

  if(s_allDecls.find(m_id) == s_allDecls.end())
    s_allDecls.insert(std::pair<uint32_t, KLDecl*>(m_id, this));

  const char * owningExtName = getStringDictValue("owningExtName");
  if(owningExtName)
    m_extension = owningExtName;      
}

KLDecl::~KLDecl()
{
  WriteLock w_lock(gKLDeclLock);

  std::map<uint32_t, KLDecl*>::iterator it = s_allDecls.find(m_id);
  if(it != s_allDecls.end())
    s_allDecls.erase(it);
}

uint32_t KLDecl::getID() const
{
  return m_id;
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

uint32_t KLDecl::getArraySize() const
{
  if(!m_data->isArray())
    return 0;
  return m_data->getArraySize();
}

const char * KLDecl::getStringArrayElement(uint32_t index) const
{
  JSONData value = getArrayElement(index);
  if(!value)
    return NULL;
  if(!value->isString())
    throw(FabricCore::Exception("KLDecl::getStringArrayElement called on non-string array element."));
  return value->getStringData();
}

const char * KLDecl::getStringDictValue(const char * key) const
{
  JSONData value = getDictValue(key);
  if(!value)
    return NULL;
  if(!value->isString())
    throw(FabricCore::Exception("KLDecl::getStringDictValue called on non-string dict element."));
  return value->getStringData();
}

JSONData KLDecl::getArrayElement(uint32_t index) const
{
  if(!m_data->isArray())
    throw(FabricCore::Exception("KLDecl::getArrayElement called on non-array data."));
  return m_data->getArrayElement(index);
}

JSONData KLDecl::getDictValue(const char * key) const
{
  if(!m_data->isDict())
    return NULL;
  return m_data->getDictValue(key);
}

JSONData KLDecl::getArrayDictValue(const char * key) const
{
  JSONData result = getDictValue(key);
  if(!result)
    return NULL;
  if(!result->isArray())
    throw(FabricCore::Exception("KLDecl::getArrayDictValue called on non-array dict element."));
  return result;
}

const KLDecl * KLDecl::getKLDeclByID(uint32_t id)
{
  std::map<uint32_t, KLDecl*>::iterator it = s_allDecls.find(id);
  if(it != s_allDecls.end())
    return it->second;
  return NULL;
}
