// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLASTManager.h"
#include "KLTypeOp.h"

#include <boost/algorithm/string.hpp>
#include <boost/range/algorithm/remove_if.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

using namespace FabricServices::ASTWrapper;

KLASTManager::KLASTManager(const FabricCore::Client * client)
{
  m_client = client;
  m_maxDeclId = 0;
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
  extension->parse();
  return extension;
}

const KLExtension* KLASTManager::loadExtension(const char * jsonFilePath)
{
  KLExtension * extension = new KLExtension(this, jsonFilePath);
  m_extensions.push_back(extension);
  extension->parse();
  return extension;
}

void KLASTManager::loadAllExtensionsInFolder(const char * extensionFolder, bool parseExtensions)
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
          if(fileName.length() <=9)
            continue;
          if(fileName.substr(fileName.length()-9, 9) == ".fpm.json")
          {
            try
            {
              KLExtension * extension = new KLExtension(this, dir->path().string().c_str());
              m_extensions.push_back(extension);
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

  if(parseExtensions)
  {
    for(uint32_t i=0;i<m_extensions.size();i++)
    {
      KLExtension * klExtension = (KLExtension *)m_extensions[i];
      klExtension->parse();
    }
  }
}

bool KLASTManager::loadAllExtensionsFromExtsPath()
{
  if(m_extensions.size() >  0)
    return false;

  const char * FABRIC_EXTS_PATH = getenv("FABRIC_EXTS_PATH");
  if(!FABRIC_EXTS_PATH)
    return false;

  std::vector<std::string> folders;
#ifdef _WIN32
  boost::split(folders, FABRIC_EXTS_PATH, boost::is_any_of(";"));
#else
  boost::split(folders, FABRIC_EXTS_PATH, boost::is_any_of(":"));
#endif

  for(size_t i=0;i<folders.size();i++)
  {
    loadAllExtensionsInFolder(folders[i].c_str(), false);
  }

  for(uint32_t i=0;i<m_extensions.size();i++)
  {
    KLExtension * klExtension = (KLExtension *)m_extensions[i];
    klExtension->parse();
  }

  return m_extensions.size() > 0;
}

const KLExtension* KLASTManager::loadExtensionFromExtsPath(const char * name)
{
  if(getExtension(name))
    return NULL;

  const char * FABRIC_EXTS_PATH = getenv("FABRIC_EXTS_PATH");
  if(!FABRIC_EXTS_PATH)
    return NULL;

  std::vector<std::string> foldersStr;
#ifdef _WIN32
  boost::split(foldersStr, FABRIC_EXTS_PATH, boost::is_any_of(";"));
#else
  boost::split(foldersStr, FABRIC_EXTS_PATH, boost::is_any_of(":"));
#endif

  std::vector<boost::filesystem::path> folders;
  for(size_t i=0;i<foldersStr.size();i++)
    folders.push_back(foldersStr[i]);

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
          if(fileName != std::string(name) + ".fpm.json")
            continue;
          try
          {
            KLExtension * extension = new KLExtension(this, dir->path().string().c_str());
            m_extensions.push_back(extension);
            extension->parse();
            return extension;
          }
          catch(FabricCore::Exception e)
          {
            printf("[KLASTManager] Ignoring extension '%s': '%s'.\n", dir->path().string().c_str(), e.getDesc_cstr());
          }
        }
      }
    }
  }
  return NULL;
}

bool KLASTManager::removeExtension(const char * name, const char * versionRequirement)
{
  const KLExtension * extension = getExtension(name, versionRequirement);
  if(extension)
  {
    for(size_t i=0;i<m_extensions.size();i++)
    {
      if(m_extensions[i] == extension)
      {
        delete(m_extensions[i]);
        m_extensions.erase(m_extensions.begin() + i);
        return true;
      }
    }
  }
  return false;
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

const KLType* KLASTManager::getKLTypeByName(const char * name, const KLDecl* decl) const
{
  // first check withinour own extension
  if(decl)
  {
    std::vector<const KLType*> types = decl->getExtension()->getTypes();
    for(uint32_t i=0;i<types.size();i++)
    {
      if(types[i]->getName() == name)
        return types[i];
    }

    // if the type isn't inside our own extension,
    // get all requires and find the corresponding matching extensions
    std::vector<const KLRequire*> requires = decl->getExtension()->getRequires();
    for(uint32_t i=0;i<requires.size();i++)
    {
      const KLExtension* extension = getExtension(requires[i]);
      if(extension)
      {
        std::vector<const KLType*> types = extension->getTypes();
        for(uint32_t j=0;j<types.size();j++)
        {
          if(types[j]->getName() == name)
            return types[j];
        }
      }
    }
  }
  
  // if we don't have it in the provided extension, check the global map
  // go backwards since we want to check highest extension versions first
  std::vector<const KLType*> types = getTypes();
  for(long int i=types.size()-1;i>=0;i--)
  {
    if(types[i]->getName() == name)
      return types[i];
  }

  return NULL;
}

const KLType* KLASTManager::getKLTypeByName(const char * name, const char * extension, const char * versionRequirement) const
{
  const KLExtension* ext = getExtension(extension, versionRequirement);
  if(ext)
  {
    std::vector<const KLType*> types = ext->getTypes();
    for(uint32_t j=0;j<types.size();j++)
    {
      if(types[j]->getName() == name)
        return types[j];
    }
  }
  return NULL;
}

const KLExtension* KLASTManager::getExtension(const char * name, const char * versionRequirement) const
{
  std::map<KLExtension::Version, const KLExtension*> extensions;
  for(uint32_t i=0;i<m_extensions.size();i++) {
    if(std::string(m_extensions[i]->getName()) != name)
      continue;
    if(extensions.find(m_extensions[i]->getVersion()) != extensions.end())
      continue;
    extensions.insert(std::pair<KLExtension::Version, const KLExtension*>(m_extensions[i]->getVersion(), m_extensions[i]));
  }
  
  std::string r = versionRequirement;
  r.erase(boost::remove_if(r, boost::is_any_of(" \t")), r.end());

  KLTypeOp::OpType op = KLTypeOp::OpType_Equal;
  if(r.substr(0, 2) == "==")
  {
    op = KLTypeOp::OpType_Equal;
    r = r.substr(2, 10000);
  }
  else if(r.substr(0, 2) == "!=")
  {
    op = KLTypeOp::OpType_NotEqual;
    r = r.substr(2, 10000);
  }
  else if(r.substr(0, 2) == ">=")
  {
    op = KLTypeOp::OpType_GreaterEquals;
    r = r.substr(2, 10000);
  }
  else if(r.substr(0, 2) == "<=")
  {
    op = KLTypeOp::OpType_LessEquals;
    r = r.substr(2, 10000);
  }
  else if(r.substr(0, 1) == ">")
  {
    op = KLTypeOp::OpType_GreaterThan;
    r = r.substr(1, 10000);
  }
  else if(r.substr(0, 1) == "<")
  {
    op = KLTypeOp::OpType_LessThan;
    r = r.substr(1, 10000);
  }

  KLExtension::Version rVersion;
  if(r.length() > 1)
  {
    std::vector<std::string> strParts;
    boost::split(strParts, r, boost::is_any_of("."));

    std::vector<int> intParts;
    for(uint32_t i=0;i<strParts.size();i++)
      intParts.push_back(atoi(strParts[i].c_str()));

    if(intParts.size() < 1) intParts.push_back(1);
    if(intParts.size() < 2) intParts.push_back(0);
    if(intParts.size() < 3) intParts.push_back(0);

    rVersion.major = intParts[0];
    rVersion.minor = intParts[1];
    rVersion.revision = intParts[2];
  }

  std::map<KLExtension::Version, const KLExtension*>::const_reverse_iterator it;
  for(it = extensions.rbegin(); it != extensions.rend(); it++)
  {
    if(r == "*")
      return it->second;

    switch(op)
    {
      case KLTypeOp::OpType_Equal:
      {
        if(it->second->getVersion() == rVersion)
          return it->second;
        break;
      }
      case KLTypeOp::OpType_NotEqual:
      {
        if(it->second->getVersion() != rVersion)
          return it->second;
        break;
      }
      case KLTypeOp::OpType_GreaterThan:
      {
        if(it->second->getVersion() > rVersion)
          return it->second;
        break;
      }
      case KLTypeOp::OpType_LessThan:
      {
        if(it->second->getVersion() < rVersion)
          return it->second;
        break;
      }
      case KLTypeOp::OpType_GreaterEquals:
      {
        if(it->second->getVersion() > rVersion || it->second->getVersion() == rVersion)
          return it->second;
        break;
      }
      case KLTypeOp::OpType_LessEquals:
      {
        if(it->second->getVersion() < rVersion || it->second->getVersion() == rVersion)
          return it->second;
        break;
      }
      default:
        break;
    }
  }

  return NULL;
}

const KLExtension* KLASTManager::getExtension(const KLRequire* require) const
{
  return getExtension(require->getRequiredExtension().c_str(), require->getVersionRange().c_str());
}

uint32_t KLASTManager::generateDeclId()
{
  return m_maxDeclId++;
}
