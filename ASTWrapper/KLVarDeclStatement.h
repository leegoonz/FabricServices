// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __ASTWrapper_KLVarDeclStatement__
#define __ASTWrapper_KLVarDeclStatement__

#include "KLStatement.h"

#include <string>

namespace FabricServices
{

  namespace ASTWrapper
  {
    class KLVarDeclStatement : public KLStatement
    {
      friend class KLFunction;
      friend class KLStatement;

    public:

      virtual ~KLVarDeclStatement() {}

      virtual KLDeclType getDeclType() const;
      virtual bool isOfDeclType(KLDeclType type) const;

      std::string getBaseType() const;
      uint32_t getCount() const;
      const std::string & getName(uint32_t index) const;
      const std::string & getArrayModifier(uint32_t index) const;

    protected:

      KLVarDeclStatement(const KLFile* klFile, JSONData data, KLStatement * parent = NULL);

      std::string m_baseType;
      std::vector<std::string> m_names;
      std::vector<std::string> m_arrayModifiers;
    };

  };

};


#endif // __ASTWrapper_KLVarDeclStatement__
