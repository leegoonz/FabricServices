// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLFile__
#define __ASTWrapper_KLFile__

#include "KLDeclContainer.h"
#include "KLStatementSearch.h"
#include <vector>

namespace FabricServices
{

  namespace ASTWrapper
  {
    // forward decl
    class KLExtension;

    class KLFile : public KLDeclContainer, public KLStatementSearch
    {
      friend class KLExtension;
      
    public:

      virtual ~KLFile();

      const KLExtension* getExtension() const;
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

      virtual const KLStatement * getStatementFromCursor(uint32_t line, uint32_t column) const;

    protected:
      
      KLFile(const KLExtension* extension, const char * filePath, const char * klCode);
      void parse();

    private:
      bool m_parsed;
      const KLExtension* m_extension;
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

#include "KLExtension.h"

#endif // __ASTWrapper_KLFile__
