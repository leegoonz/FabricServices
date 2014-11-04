// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLExtension__
#define __ASTWrapper_KLExtension__

#include "KLDeclContainer.h"
#include "KLFile.h"

namespace FabricServices
{

  namespace ASTWrapper
  {

    class KLExtension : public KLDeclContainer
    {
      friend class KLASTManager;

    public:

      virtual ~KLExtension();

      const char * getName() const;
      const char * getVersion() const;

      std::vector<const KLFile*> getFiles() const;

      // decl vector getters
      virtual std::vector<const KLRequire*> getRequires() const;
      virtual std::vector<const KLAlias*> getAliases() const;
      virtual std::vector<const KLConstant*> getConstants() const;
      virtual std::vector<const KLType*> getTypes() const;
      virtual std::vector<const KLFunction*> getFunctions() const;
      virtual std::vector<const KLOperator*> getOperators() const;

      // decl vector getter overloads
      virtual std::vector<const KLInterface*> getInterfaces() const;
      virtual std::vector<const KLStruct*> getStructs() const;
      virtual std::vector<const KLObject*> getObjects() const;

    protected:
      
      KLExtension(const FabricCore::Client * client, const char * jsonFilePath);
      KLExtension(const FabricCore::Client * client, const char * name, const char * jsonContent, uint32_t numKLFiles, const char ** klContent);

    private:

      void init(const FabricCore::Client * client, const char * jsonContent, uint32_t numKLFiles, const char ** klContent);
      std::vector<std::string> extractKLFilePaths(JSONData data, const char * extensionName);

      std::string m_name;
      std::string m_version;
      std::vector<const KLFile*> m_files;
    };

  };

};

#endif // __ASTWrapper_KLExtension__
