// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLFile.h"

#include <boost/filesystem/path.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/shared_mutex.hpp>
typedef boost::shared_mutex Lock;
typedef boost::unique_lock< Lock >  WriteLock;
typedef boost::shared_lock< Lock >  ReadLock;
Lock gKLFileLock;

using namespace FabricServices::ASTWrapper;

KLFile::KLFile(const char * extension, const char * filePath, const char * klCode)
{
  WriteLock w_lock(gKLFileLock);

  m_extension = extension;
  m_filePath = filePath;
  m_klCode = klCode;

  boost::filesystem::path path = m_filePath;
  m_fileName = path.stem().string();

  printf("filepath '%s', filename '%s'\n", m_filePath.c_str(), m_fileName.c_str());
}

KLFile::~KLFile()
{
}

std::vector<const KLRequire*> KLFile::getRequires() const
{
  return m_requires;
}

std::vector<const KLAlias*> KLFile::getAliases() const
{
  return m_aliases;
}

std::vector<const KLConstant*> KLFile::getConstants() const
{
  return m_constants;
}

std::vector<const KLType*> KLFile::getTypes() const
{
  return m_types;
}

std::vector<const KLFunction*> KLFile::getFunctions() const
{
  return m_functions;
}

std::vector<const KLInterface*> KLFile::getInterfaces() const
{
  std::vector<const KLInterface*> result;
  for(uint32_t i=0;i<m_types.size();i++)
  {
    if(m_types[i]->getKLType() == std::string("interface"))
      result.push_back((const KLInterface*)m_types[i]);
  }
  return result;
}

std::vector<const KLStruct*> KLFile::getStructs() const
{
  std::vector<const KLStruct*> result;
  for(uint32_t i=0;i<m_types.size();i++)
  {
    if(m_types[i]->getKLType() == std::string("struct"))
      result.push_back((const KLStruct*)m_types[i]);
  }
  return result;
}

std::vector<const KLObject*> KLFile::getObjects() const
{
  std::vector<const KLObject*> result;
  for(uint32_t i=0;i<m_types.size();i++)
  {
    if(m_types[i]->getKLType() == std::string("object"))
      result.push_back((const KLObject*)m_types[i]);
  }
  return result;
}

std::vector<const KLOperator*> KLFile::getOperators() const
{
  std::vector<const KLOperator*> result;
  for(uint32_t i=0;i<m_functions.size();i++)
  {
    if(m_functions[i]->getKLType() == std::string("operator"))
      result.push_back((const KLOperator*)m_functions[i]);
  }
  return result;
}

const KLConstant* KLFile::getConstant(const char * name) const
{
  for(uint32_t i=0;i<m_constants.size();i++)
  {
    if(m_constants[i]->getName() == name)
      return m_constants[i];
  }
  return NULL;
}

const KLFunction* KLFile::getFunction(const char * name) const
{
  for(uint32_t i=0;i<m_functions.size();i++)
  {
    if(m_functions[i]->getName() == name)
      return m_functions[i];
  }
  return NULL;
}

const KLOperator* KLFile::getOperator(const char * name) const
{
  for(uint32_t i=0;i<m_functions.size();i++)
  {
    if(m_functions[i]->getName() == name)
    {
      if(m_functions[i]->getKLType() == std::string("operator"))
      {
        return (const KLOperator*)m_functions[i];
      }
    }
  }
  return NULL;
}

