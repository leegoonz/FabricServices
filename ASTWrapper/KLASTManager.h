// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLASTManager__
#define __ASTWrapper_KLASTManager__

#include "KLDeclContainer.h"
#include "KLExtension.h"

namespace FabricServices
{

  namespace ASTWrapper
  {

    class KLASTManager : public KLDeclContainer
    {
    public:

      KLASTManager(const FabricCore::Client * client);
      virtual ~KLASTManager();

      const FabricCore::Client* getClient() const;

      const KLExtension* loadExtension(const char * name, const char * jsonContent, uint32_t numKlFiles, const char ** klContent);
      const KLExtension* loadExtension(const char * jsonFilePath);
      void loadAllExtensionsInFolder(const char * extensionFolder);

      std::vector<const KLExtension*> getExtensions() const;

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

    private:
      const FabricCore::Client * m_client;
      std::vector<const KLExtension*> m_extensions;
    };

  };

};

#endif // __ASTWrapper_KLASTManager__
