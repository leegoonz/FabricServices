// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLFile__
#define __ASTWrapper_KLFile__

#include "KLDeclContainer.h"
#include <vector>

namespace FabricServices
{

  namespace ASTWrapper
  {

    class KLFile : public KLDeclContainer
    {
    public:

      KLFile(const FabricCore::Client * client, const char * extension, const char * filePath, const char * klCode);
      virtual ~KLFile();

      const char * getExtension() const;
      const char * getFilePath() const;
      const char * getFileName() const;
      const char * getKLCode() const;

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

      // single decl getters
      virtual const KLConstant* getConstant(const char * name) const;
      virtual const KLFunction* getFunction(const char * name) const;
      virtual const KLOperator* getOperator(const char * name) const;

    private:
      std::string m_extension;
      std::string m_filePath;
      std::string m_fileName;
      std::string m_klCode;
      std::vector<const KLRequire*> m_requires;
      std::vector<const KLAlias*> m_aliases;
      std::vector<const KLConstant*> m_constants;
      std::vector<const KLType*> m_types;
      std::vector<const KLFunction*> m_functions;
      std::vector<const KLOperator*> m_operators;
    };

  };

};

#endif // __ASTWrapper_KLFile__
