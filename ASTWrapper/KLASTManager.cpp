// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLASTManager.h"

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

using namespace FabricServices::ASTWrapper;

KLASTManager::KLASTManager(const FabricCore::Client * client)
{
  m_client = client;
}

KLASTManager::~KLASTManager()
{
  for(uint32_t i=0;i<m_extensions.size();i++)
    delete(m_extensions[i]);
}

const FabricCore::Client* KLASTManager::getClient() const
{
  return m_client;
}

const KLExtension* KLASTManager::loadExtension(const char * name, const char * jsonContent, uint32_t numKlFiles, const char ** klContent)
{
  KLExtension * extension = new KLExtension(this, name, jsonContent, numKlFiles, klContent);
  m_extensions.push_back(extension);
  return extension;
}

const KLExtension* KLASTManager::loadExtension(const char * jsonFilePath)
{
  KLExtension * extension = new KLExtension(this, jsonFilePath);
  m_extensions.push_back(extension);
  return extension;
}

void KLASTManager::loadAllExtensionsInFolder(const char * extensionFolder)
{
  std::vector<boost::filesystem::path> folders;
  folders.push_back(extensionFolder);

  for(uint32_t i=0;i<folders.size();i++)
  {
    if( boost::filesystem::exists(folders[i])) {
      for ( boost::filesystem::directory_iterator end, dir(folders[i]); dir != end; ++dir ) {
        std::string fileName = dir->path().filename().string();
        if(fileName == "." || fileName == "..")
          continue;
        if(boost::filesystem::is_directory(dir->path()))
        {
          folders.push_back(dir->path().string());
        }
        else
        {
          if(fileName.substr(fileName.length()-9, 9) == ".fpm.json")
          {
            try
            {
              KLExtension * extension = new KLExtension(this, dir->path().string().c_str());
            }
            catch(FabricCore::Exception e)
            {
              printf("[KLASTManager] Ignoring extension '%s': '%s'.\n", dir->path().string().c_str(), e.getDesc_cstr());
            }
          }
        }
      }
    }
  }
}

std::vector<const KLExtension*> KLASTManager::getExtensions() const
{
  return m_extensions;
}

std::vector<const KLRequire*> KLASTManager::getRequires() const
{
  std::vector<const KLRequire*> result;
  for(uint32_t i=0;i<m_extensions.size();i++)
  {
    std::vector<const KLRequire*> singleResult = m_extensions[i]->getRequires();
    result.insert(result.end(), singleResult.begin(), singleResult.end());
  }
  return result;
}

std::vector<const KLAlias*> KLASTManager::getAliases() const
{
  std::vector<const KLAlias*> result;
  for(uint32_t i=0;i<m_extensions.size();i++)
  {
    std::vector<const KLAlias*> singleResult = m_extensions[i]->getAliases();
    result.insert(result.end(), singleResult.begin(), singleResult.end());
  }
  return result;
}

std::vector<const KLConstant*> KLASTManager::getConstants() const
{
  std::vector<const KLConstant*> result;
  for(uint32_t i=0;i<m_extensions.size();i++)
  {
    std::vector<const KLConstant*> singleResult = m_extensions[i]->getConstants();
    result.insert(result.end(), singleResult.begin(), singleResult.end());
  }
  return result;
}

std::vector<const KLType*> KLASTManager::getTypes() const
{
  std::vector<const KLType*> result;
  for(uint32_t i=0;i<m_extensions.size();i++)
  {
    std::vector<const KLType*> singleResult = m_extensions[i]->getTypes();
    result.insert(result.end(), singleResult.begin(), singleResult.end());
  }
  return result;
}

std::vector<const KLFunction*> KLASTManager::getFunctions() const
{
  std::vector<const KLFunction*> result;
  for(uint32_t i=0;i<m_extensions.size();i++)
  {
    std::vector<const KLFunction*> singleResult = m_extensions[i]->getFunctions();
    result.insert(result.end(), singleResult.begin(), singleResult.end());
  }
  return result;
}

std::vector<const KLInterface*> KLASTManager::getInterfaces() const
{
  std::vector<const KLInterface*> result;
  for(uint32_t i=0;i<m_extensions.size();i++)
  {
    std::vector<const KLInterface*> singleResult = m_extensions[i]->getInterfaces();
    result.insert(result.end(), singleResult.begin(), singleResult.end());
  }
  return result;
}

std::vector<const KLStruct*> KLASTManager::getStructs() const
{
  std::vector<const KLStruct*> result;
  for(uint32_t i=0;i<m_extensions.size();i++)
  {
    std::vector<const KLStruct*> singleResult = m_extensions[i]->getStructs();
    result.insert(result.end(), singleResult.begin(), singleResult.end());
  }
  return result;
}

std::vector<const KLObject*> KLASTManager::getObjects() const
{
  std::vector<const KLObject*> result;
  for(uint32_t i=0;i<m_extensions.size();i++)
  {
    std::vector<const KLObject*> singleResult = m_extensions[i]->getObjects();
    result.insert(result.end(), singleResult.begin(), singleResult.end());
  }
  return result;
}

std::vector<const KLOperator*> KLASTManager::getOperators() const
{
  std::vector<const KLOperator*> result;
  for(uint32_t i=0;i<m_extensions.size();i++)
  {
    std::vector<const KLOperator*> singleResult = m_extensions[i]->getOperators();
    result.insert(result.end(), singleResult.begin(), singleResult.end());
  }
  return result;
}


