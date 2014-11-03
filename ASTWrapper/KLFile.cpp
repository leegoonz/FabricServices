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

KLFile::KLFile(const FabricCore::Client * client, const char * extension, const char * filePath, const char * klCode)
{
  WriteLock w_lock(gKLFileLock);

  m_extension = extension;
  m_filePath = filePath;
  m_klCode = klCode;

  boost::filesystem::path path = m_filePath;
  m_fileName = path.stem().string() + ".kl";

  FabricCore::RTVal jsonVal = GetKLJSONAST(*client, klCode, false);
  std::string jsonStr = jsonVal.getStringCString();

  FabricCore::Variant variant = FabricCore::Variant::CreateFromJSON(jsonStr.c_str());

  for(uint32_t i=0;i<variant.getArraySize();i++)
  {
    const FabricCore::Variant * element = variant.getArrayElement(i);
    if(!element->isDict())
      continue;
    const FabricCore::Variant * etVar = element->getDictValue("type");
    if(!etVar)
      continue;
    if(!etVar->isString())
      continue;

    std::string et = etVar->getStringData();
    if(et == "RequireGlobal")
    {
      KLRequire * e = new KLRequire(element);
      m_requires.push_back(e);
    }
    else if(et == "Alias")
    {
      KLAlias * e = new KLAlias(element);
      m_aliases.push_back(e);
    }
    else if(et == "GlobalConstDecl")
    {
      KLConstant * e = new KLConstant(element);
      m_constants.push_back(e);
    }
    else if(et == "Function")
    {
      KLFunction * e = new KLFunction(element);
      m_functions.push_back(e);
    }
    else if(et == "Operator")
    {
      KLOperator * e = new KLOperator(element);
      m_operators.push_back(e);
    }
    else if(et == "ASTStructDecl")
    {
      KLStruct * e = new KLStruct(element);
      m_types.push_back(e);
    }
    else if(et == "MethodOpImpl")
    {
      KLMethod * e = new KLMethod(element);
      std::string thisType = e->getThisType();
      const KLType * klType = KLType::getKLTypeByName(thisType.c_str());
      if(klType)
        klType->pushMethod(e);
      else
        m_functions.push_back(e);
    }
    else
    {
      std::string message = "Unknown AST token '"+et+"'.";
      throw(FabricCore::Exception(message.c_str(), message.length()));
      return;
    }
  }
}

KLFile::~KLFile()
{
  for(uint32_t i=0;i<m_requires.size();i++)
    delete(m_requires[i]);
  for(uint32_t i=0;i<m_aliases.size();i++)
    delete(m_aliases[i]);
  for(uint32_t i=0;i<m_constants.size();i++)
    delete(m_constants[i]);
  for(uint32_t i=0;i<m_types.size();i++)
    delete(m_types[i]);
  for(uint32_t i=0;i<m_functions.size();i++)
    delete(m_functions[i]);
  for(uint32_t i=0;i<m_operators.size();i++)
    delete(m_operators[i]);
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
  return m_operators;
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
  for(uint32_t i=0;i<m_operators.size();i++)
  {
    if(m_operators[i]->getName() == name)
    {
      return m_operators[i];
    }
  }
  return NULL;
}

