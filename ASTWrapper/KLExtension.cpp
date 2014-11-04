// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLExtension.h"

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

using namespace FabricServices::ASTWrapper;

KLExtension::KLExtension(const KLASTManager* astManager, const char * jsonFilePath)
{
  m_astManager = astManager;

  boost::filesystem::path jsonPath = jsonFilePath;
  m_name = jsonPath.filename().string();

  FILE * jsonFile = fopen(jsonFilePath, "rb");
  if(!jsonFile)
  {
    std::string message = "KLExtension: jsonFilePath '";
    message += jsonFilePath;
    message += "' does not exist.";
    throw(FabricCore::Exception(message.c_str()));
  }

  fseek( jsonFile, 0, SEEK_END );
  int jsonFileSize = ftell( jsonFile );
  rewind( jsonFile );

  char * jsonFileBuffer = (char*) malloc(jsonFileSize + 1);
  jsonFileBuffer[jsonFileSize] = '\0';

  fread(jsonFileBuffer, jsonFileSize, 1, jsonFile);
  fclose(jsonFile);

  std::string jsonContent = jsonFileBuffer;
  free(jsonFileBuffer);

  FabricCore::Variant jsonVar = FabricCore::Variant::CreateFromJSON(jsonContent.c_str());
  
  std::vector<std::string> klFileRelPaths = extractKLFilePaths(&jsonVar, m_name.c_str());
  std::vector<std::string> klContent;
  std::vector<const char *> klContentCStr;
  for(uint32_t i=0;i<klFileRelPaths.size();i++)
  {
    boost::filesystem::path klFilePath = klFileRelPaths[i];
    if(!klFilePath.is_absolute())
      klFilePath = jsonPath.parent_path() / klFilePath;

    if(!boost::filesystem::exists(klFilePath))
    {
      std::string message = "KLExtension: '" + m_name + "' uses a non existing KL file '";
      message += klFilePath.string();
      message += "'.";
      throw(FabricCore::Exception(message.c_str()));
    }

    FILE * klFile = fopen(klFilePath.string().c_str(), "rb");

    fseek( klFile, 0, SEEK_END );
    int klFileSize = ftell( klFile );
    rewind( klFile );

    char * klFileBuffer = (char*) malloc(klFileSize + 1);
    klFileBuffer[klFileSize] = '\0';

    fread(klFileBuffer, klFileSize, 1, klFile);
    fclose(klFile);

    klContent.push_back(klFileBuffer);
    klContentCStr.push_back(klContent[i].c_str());
    free(klFileBuffer);
  }

  init(jsonContent.c_str(), klContentCStr.size(), &klContentCStr[0]);
}

KLExtension::KLExtension(const KLASTManager* astManager, const char * name, const char * jsonContent, uint32_t numKLFiles, const char ** klContent)
{
  m_astManager = astManager;
  m_name = name;
  init(jsonContent, numKLFiles, klContent);
}

KLExtension::~KLExtension()
{
  for(uint32_t i=0;i<m_files.size();i++)
    delete(m_files[i]);
}

void KLExtension::init(const char * jsonContent, uint32_t numKLFiles, const char ** klContent)
{
  const FabricCore::Client * client = m_astManager->getClient();

  FabricCore::Variant jsonVar = FabricCore::Variant::CreateFromJSON(jsonContent);

  if(!jsonVar.isDict())
  {
    std::string message = "KLExtension: The extension '";
    message += m_name;
    message += "' does not contain a json dictionary.";
    throw(FabricCore::Exception(message.c_str()));
  }

  JSONData versionVar = jsonVar.getDictValue("version");
  if(versionVar)
  {
    if(versionVar->isString())
    {
      m_version = versionVar->getStringData();
    }
    else
    {
      std::string message = "KLExtension: The extension '";
      message += m_name;
      message += "' contains an invalid version dictionary value (not string).";
      throw(FabricCore::Exception(message.c_str()));
    }
  }
  else
    m_version = "1.0.0";

  std::vector<std::string> klFilePaths = extractKLFilePaths(&jsonVar, m_name.c_str());
  if(klFilePaths.size() != numKLFiles)
  {
    std::string message = "KLExtension: The number of provided KL sources for extension '";
    message += m_name;
    message += "' does not match the code dictionary value in json.";
    throw(FabricCore::Exception(message.c_str()));
  }

  for(uint32_t i=0;i<klFilePaths.size();i++)
  {
    KLFile * klFile = new KLFile(this, klFilePaths[i].c_str(), klContent[i]);
    m_files.push_back(klFile);
  }
}

std::vector<std::string> KLExtension::extractKLFilePaths(JSONData data, const char * extensionName)
{
  std::vector<std::string> result;

  if(!data->isDict())
  {
    std::string message = "KLExtension: The extension '";
    message += extensionName;
    message += "' does not contain a json dictionary.";
    throw(FabricCore::Exception(message.c_str()));
  }

  JSONData codeVar = data->getDictValue("code");
  if(!codeVar)
  {
    std::string message = "KLExtension: The extension '";
    message += extensionName;
    message += "' does not contain a code dictionary value.";
    throw(FabricCore::Exception(message.c_str()));
  }

  if(codeVar->isString())
  {
    result.push_back(codeVar->getStringData());
  }
  else if(codeVar->isArray())
  {
    for(uint32_t i=0;i<codeVar->getArraySize();i++)
    {
      JSONData singleCodeVar = codeVar->getArrayElement(i);
      if(singleCodeVar->isString())
      {
        result.push_back(singleCodeVar->getStringData());
      }
      else
      {
        std::string message = "KLExtension: The extension '";
        message += extensionName;
        message += "' contains a code array with an invalid element.";
        throw(FabricCore::Exception(message.c_str()));
      }
    }
  }
  else
  {
    std::string message = "KLExtension: The extension '";
    message += extensionName;
    message += "' contains an invalid code dictionary value (neither string nor array).";
    throw(FabricCore::Exception(message.c_str()));
  }

  return result;
}

const KLASTManager * KLExtension::getASTManager() const
{
  return m_astManager;
}

const char * KLExtension::getName() const
{
  return m_name.c_str();
}

const char * KLExtension::getVersion() const
{
  return m_version.c_str();
}

std::vector<const KLFile*> KLExtension::getFiles() const
{
  return m_files;
}

std::vector<const KLRequire*> KLExtension::getRequires() const
{
  std::vector<const KLRequire*> result;
  for(uint32_t i=0;i<m_files.size();i++)
  {
    std::vector<const KLRequire*> singleResult = m_files[i]->getRequires();
    result.insert(result.end(), singleResult.begin(), singleResult.end());
  }
  return result;
}

std::vector<const KLAlias*> KLExtension::getAliases() const
{
  std::vector<const KLAlias*> result;
  for(uint32_t i=0;i<m_files.size();i++)
  {
    std::vector<const KLAlias*> singleResult = m_files[i]->getAliases();
    result.insert(result.end(), singleResult.begin(), singleResult.end());
  }
  return result;
}

std::vector<const KLConstant*> KLExtension::getConstants() const
{
  std::vector<const KLConstant*> result;
  for(uint32_t i=0;i<m_files.size();i++)
  {
    std::vector<const KLConstant*> singleResult = m_files[i]->getConstants();
    result.insert(result.end(), singleResult.begin(), singleResult.end());
  }
  return result;
}

std::vector<const KLType*> KLExtension::getTypes() const
{
  std::vector<const KLType*> result;
  for(uint32_t i=0;i<m_files.size();i++)
  {
    std::vector<const KLType*> singleResult = m_files[i]->getTypes();
    result.insert(result.end(), singleResult.begin(), singleResult.end());
  }
  return result;
}

std::vector<const KLFunction*> KLExtension::getFunctions() const
{
  std::vector<const KLFunction*> result;
  for(uint32_t i=0;i<m_files.size();i++)
  {
    std::vector<const KLFunction*> singleResult = m_files[i]->getFunctions();
    result.insert(result.end(), singleResult.begin(), singleResult.end());
  }
  return result;
}

std::vector<const KLInterface*> KLExtension::getInterfaces() const
{
  std::vector<const KLInterface*> result;
  for(uint32_t i=0;i<m_files.size();i++)
  {
    std::vector<const KLInterface*> singleResult = m_files[i]->getInterfaces();
    result.insert(result.end(), singleResult.begin(), singleResult.end());
  }
  return result;
}

std::vector<const KLStruct*> KLExtension::getStructs() const
{
  std::vector<const KLStruct*> result;
  for(uint32_t i=0;i<m_files.size();i++)
  {
    std::vector<const KLStruct*> singleResult = m_files[i]->getStructs();
    result.insert(result.end(), singleResult.begin(), singleResult.end());
  }
  return result;
}

std::vector<const KLObject*> KLExtension::getObjects() const
{
  std::vector<const KLObject*> result;
  for(uint32_t i=0;i<m_files.size();i++)
  {
    std::vector<const KLObject*> singleResult = m_files[i]->getObjects();
    result.insert(result.end(), singleResult.begin(), singleResult.end());
  }
  return result;
}

std::vector<const KLOperator*> KLExtension::getOperators() const
{
  std::vector<const KLOperator*> result;
  for(uint32_t i=0;i<m_files.size();i++)
  {
    std::vector<const KLOperator*> singleResult = m_files[i]->getOperators();
    result.insert(result.end(), singleResult.begin(), singleResult.end());
  }
  return result;
}


