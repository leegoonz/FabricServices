// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLFile.h"
#include "KLLocation.h"

#include <boost/filesystem/path.hpp>
#include <boost/algorithm/string.hpp>

using namespace FabricServices::ASTWrapper;

KLFile::KLFile(const KLExtension* extension, const char * filePath, const char * klCode)
{
  m_extension = extension;
  m_filePath = filePath;

  boost::filesystem::path path = m_filePath;
  m_fileName = path.stem().string() + ".kl";

  path = extension->getFilePath();
  path = path.parent_path() / m_filePath;
  m_absFilePath = path.string();
  
  m_klCode = klCode;
  m_parsed = false;
}

void KLFile::parse()
{
  if(m_parsed)
    return;
  m_parsed = true;

  const FabricCore::Client * client = m_extension->getASTManager()->getClient();

  try
  {
    FabricCore::RTVal jsonVal = GetKLJSONAST(*client, m_klCode.c_str(), false, m_fileName.c_str());
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
        KLRequire * e = new KLRequire(this, element);
        m_requires.push_back(e);

        // ensure to parse extensions in the right order,
        // so that we can add methods to types for example.
        KLExtension * extension = (KLExtension *)getExtension()->getASTManager()->getExtension(e);
        if(extension)
          extension->parse();
      }
      else if(et == "Alias")
      {
        KLAlias * e = new KLAlias(this, element);
        m_aliases.push_back(e);
      }
      else if(et == "GlobalConstDecl")
      {
        KLConstant * e = new KLConstant(this, element);
        m_constants.push_back(e);
      }
      else if(et == "Function")
      {
        KLFunction * e = new KLFunction(this, element);
        m_functions.push_back(e);
      }
      else if(et == "Operator")
      {
        KLOperator * e = new KLOperator(this, element);
        m_operators.push_back(e);
      }
      else if(et == "ASTStructDecl")
      {
        KLStruct * e = new KLStruct(this, element);
        m_types.push_back(e);
      }
      else if(et == "MethodOpImpl")
      {
        KLMethod * e = new KLMethod(this, element);
        std::string thisType = e->getThisType();
        const KLType * klType = m_extension->getASTManager()->getKLTypeByName(thisType.c_str(), e);
        if(klType)
        {
          if(!klType->pushMethod(e))
            m_functions.push_back(e);
        }
        else
          m_functions.push_back(e);
      }
      else if(et == "Destructor")
      {
        KLFunction function(this, element);
        std::string thisType = function.getName();
        boost::trim_left_if(thisType, boost::is_any_of("~"));
        KLMethod * e = new KLMethod(this, element, thisType);
        const KLType * klType = m_extension->getASTManager()->getKLTypeByName(thisType.c_str(), e);
        if(klType)
        {
          if(!klType->pushMethod(e))
            m_functions.push_back(e);
        }
        else
          m_functions.push_back(e);
      }
      else if(et == "ASTInterface")
      {
        KLInterface * e = new KLInterface(this, element);
        m_types.push_back(e);
      }
      else if(et == "ASTObjectDecl")
      {
        KLObject * e = new KLObject(this, element);
        m_types.push_back(e);
      }
      else if(et == "ComparisonOpImpl" ||
        et == "AssignOpImpl" ||
        et == "BinOpImpl" ||
        et == "ASTUniOpDecl")
      {
        KLTypeOp * e = new KLTypeOp(this, element);

        std::string thisType = e->getLhs();
        const KLType * klType = m_extension->getASTManager()->getKLTypeByName(thisType.c_str(), e);
        if(klType)
          klType->pushTypeOp(e);
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
  catch(FabricCore::Exception e)
  {
    std::string message = e.getDesc_cstr();
    std::vector<std::string> errors;
    boost::split(errors, message, boost::is_any_of("\n"));

    for(size_t i=0;i<errors.size();i++)
    {
      KLError error(errors[i].c_str());
      if(error.isValid())
        m_errors.push_back(new KLError(errors[i].c_str()));
    }
  }
}

KLFile::~KLFile()
{
  clear();
  for(uint32_t i=0;i<m_errors.size();i++)
    delete(m_errors[i]);
}

void KLFile::clear()
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
  m_requires.clear();
  m_aliases.clear();
  m_constants.clear();
  m_types.clear();
  m_functions.clear();
  m_operators.clear();
}

const KLExtension* KLFile::getExtension() const
{
  return m_extension;
}

const char * KLFile::getFilePath() const
{
  return m_filePath.c_str();
}

const char * KLFile::getFileName() const
{
  return m_fileName.c_str();
}

const char * KLFile::getAbsoluteFilePath() const
{
  return m_absFilePath.c_str();
}

const char * KLFile::getKLCode() const
{
  return m_klCode.c_str();
}

bool KLFile::hasErrors() const
{
  return m_errors.size() > 0;
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

std::vector<const KLError*> KLFile::getErrors() const
{
  return m_errors;
}

const KLStatement * KLFile::getStatementAtCursor(uint32_t line, uint32_t column) const
{
  uint32_t minDistance = UINT_MAX;
  const KLStatement * result = NULL;

  for(size_t i=0;i<m_functions.size();i++)
  {
    const KLStatement * statement = m_functions[i]->getStatementAtCursor(line, column);
    if(statement)
    {
      uint32_t distance = statement->getCursorDistance(line, column);
      if(distance < minDistance)
      {
        result = statement;
        minDistance = distance;
      }
      
    }
  }

  for(size_t i=0;i<m_operators.size();i++)
  {
    const KLStatement * statement = m_operators[i]->getStatementAtCursor(line, column);
    if(statement)
    {
      uint32_t distance = statement->getCursorDistance(line, column);
      if(distance < minDistance)
      {
        result = statement;
        minDistance = distance;
      }
      
    }
  }

  for(size_t i=0;i<m_types.size();i++)
  {
    for(uint32_t j=0;j<m_types[i]->getMethodCount();j++)
    {
      const KLStatement * statement = m_types[i]->getMethod(j)->getStatementAtCursor(line, column);
      if(statement)
      {
        uint32_t distance = statement->getCursorDistance(line, column);
        if(distance < minDistance)
        {
          result = statement;
          minDistance = distance;
        }
      }
    }

    for(uint32_t j=0;j<m_types[i]->getTypeOpCount();j++)
    {
      const KLStatement * statement = m_types[i]->getTypeOp(j)->getStatementAtCursor(line, column);
      if(statement)
      {
        uint32_t distance = statement->getCursorDistance(line, column);
        if(distance < minDistance)
        {
          result = statement;
          minDistance = distance;
        }
      }
    }
  }

  return result;
}

bool KLFile::updateKLCode(const char * code)
{

  std::vector<const KLRequire*> tempRequires = m_requires;
  std::vector<const KLAlias*> tempAliases = m_aliases;
  std::vector<const KLConstant*> tempConstants = m_constants;
  std::vector<const KLType*> tempTypes = m_types;
  std::vector<const KLFunction*> tempFunctions = m_functions;
  std::vector<const KLOperator*> tempOperators = m_operators;

  for(uint32_t i=0;i<m_errors.size();i++)
    delete(m_errors[i]);
  m_requires.clear();
  m_aliases.clear();
  m_constants.clear();
  m_types.clear();
  m_functions.clear();
  m_operators.clear();
  m_errors.clear();

  m_klCode = code;
  m_parsed = false;
  parse();

  if(hasErrors())
  {
    clear();
    m_requires = tempRequires;
    m_aliases = tempAliases;
    m_constants = tempConstants;
    m_types = tempTypes;
    m_functions = tempFunctions;
    m_operators = tempOperators;
  }
  else
  {
    for(uint32_t i=0;i<tempRequires.size();i++)
      delete(tempRequires[i]);
    for(uint32_t i=0;i<tempAliases.size();i++)
      delete(tempAliases[i]);
    for(uint32_t i=0;i<tempConstants.size();i++)
      delete(tempConstants[i]);
    for(uint32_t i=0;i<tempTypes.size();i++)
      delete(tempTypes[i]);
    for(uint32_t i=0;i<tempFunctions.size();i++)
      delete(tempFunctions[i]);
    for(uint32_t i=0;i<tempOperators.size();i++)
      delete(tempOperators[i]);
  }

  return hasErrors();
}
