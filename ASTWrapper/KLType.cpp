// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLType.h"

#include <map>

#include <boost/thread/locks.hpp>
#include <boost/thread/shared_mutex.hpp>
typedef boost::shared_mutex Lock;
typedef boost::unique_lock< Lock >  WriteLock;
typedef boost::shared_lock< Lock >  ReadLock;
Lock gKLTypeLock;

using namespace FabricServices::ASTWrapper;

std::map<std::string, KLType*> s_allTypes;

KLType::KLType(JSONData data)
: KLCommented(data)
{
  WriteLock w_lock(gKLTypeLock);

  const char * name = getStringDictValue("name");
  if(name)
    m_name = name;

  if(s_allTypes.find(m_name) == s_allTypes.end())
    s_allTypes.insert(std::pair<std::string, KLType*>(m_name, this));
}

KLType::~KLType()
{
  WriteLock w_lock(gKLTypeLock);

  for(uint32_t i=0;i<m_methods.size();i++)
  {
    delete(m_methods[i]);
  }

  std::map<std::string, KLType*>::iterator it = s_allTypes.find(m_name);
  if(it != s_allTypes.end())
    s_allTypes.erase(it);
}

void KLType::setExtension(const std::string & extension)
{
  KLCommented::setExtension(extension);
  for(uint32_t i=0;i<m_methods.size();i++)
    m_methods[i]->setExtension(extension);
}

void KLType::setKLFile(const std::string & klFile)
{
  KLCommented::setKLFile(klFile);
  for(uint32_t i=0;i<m_methods.size();i++)
    m_methods[i]->setKLFile(klFile);
}

const std::string & KLType::getName() const
{
  return m_name;
}

uint32_t KLType::getMethodCount() const
{
  return m_methods.size();
}

const KLMethod * KLType::getMethod(uint32_t index) const
{
  return m_methods[index];
}

const KLMethod * KLType::getMethod(const char * labelOrName) const
{
  if(!labelOrName)
    return NULL;

  std::map<std::string, uint32_t>::const_iterator it = m_methodLabelToId.find(labelOrName);
  if(it != m_methodLabelToId.end())
    return m_methods[it->second];

  for(uint32_t i=0;i<m_methods.size();i++)
  {
    if(m_methods[i]->getName() == labelOrName)
      return m_methods[i];
  }
  return NULL;
}

std::vector<const KLMethod*> KLType::getMethods(bool includeInherited, bool includeInternal, const char * category) const
{
  std::map<std::string, const KLMethod*> lookup;
  for(uint32_t i=0;i<m_methods.size();i++)
  {
    if(!includeInternal && m_methods[i]->isInternal())
      continue;

    if(category)
    {
      if(m_methods[i]->getComments()->getSingleQualifier("category", category) != category)
        continue;
    }

    std::string key = m_methods[i]->getLabel();
    lookup.insert(std::pair<std::string, const KLMethod*>(key,m_methods[i]));
  }

  if(includeInherited)
  {
    std::vector<const KLType*> parents = getParents();
    for(uint32_t i=0;i<parents.size();i++)
    {
      std::vector<const KLMethod*> methods = parents[i]->getMethods(includeInherited, includeInternal, category);
      for(uint32_t j=0;j<methods.size();j++)
      {
        if(!methods[j]->isVirtual())
          continue;
        std::string key = m_methods[j]->getLabel();
        if(lookup.find(key) != lookup.end())
          continue;
        lookup.insert(std::pair<std::string, const KLMethod*>(key,methods[j]));
      }
    }
  }

  std::vector<const KLMethod*> methods;
  for(std::map<std::string, const KLMethod*>::const_iterator it = lookup.begin(); it != lookup.end(); it++)
  {
    methods.push_back(it->second);
  }
  return methods;
}

const KLType * KLType::getKLTypeByName(const char * name)
{
  std::map<std::string, KLType*>::iterator it = s_allTypes.find(name);
  if(it != s_allTypes.end())
    return it->second;
  return NULL;
}

void KLType::pushMethod(KLMethod * method)
{
  WriteLock w_lock(gKLTypeLock);

  m_methodLabelToId.insert(std::pair<std::string, uint32_t>(method->getLabel(), (uint32_t)m_methods.size()));
  m_methods.push_back(method);
}
