// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __ASTWrapper_KLFunction__
#define __ASTWrapper_KLFunction__

#include "KLStmt.h"
#include "KLCompoundStmt.h"
#include "KLConditionalStmt.h"
#include "KLCStyleLoopStmt.h"
#include "KLSwitchStmt.h"
#include "KLCaseStmt.h"
#include "KLVarDeclStmt.h"
#include "KLExprStmt.h"
#include "KLParameter.h"

#include <string>

namespace FabricServices
{

  namespace ASTWrapper
  {

    class KLFunction : public KLStmt
    {
      friend class KLFile;

    public:

      virtual ~KLFunction();

      virtual KLDeclType getDeclType() const;
      virtual bool isOfDeclType(KLDeclType type) const;

      virtual const std::string & getName() const;
      virtual const std::string & getReturnType() const;
      virtual const std::string & getSymbolName() const;
      virtual uint32_t getParameterCount() const;
      virtual const KLParameter * getParameter(uint32_t index) const;
      virtual const KLCompoundStmt * getBody() const;

      virtual bool isMethod() const;
      virtual std::string getPrefix() const; // the prefix of the function *may* be something like 'Vec3.'
      virtual std::string getSuffix() const; // the suffix can be '!' or '?'
      virtual const char * getKLType() const;
      virtual std::string getKLCode(bool includeReturnType = true, bool includeKeyWord = true, bool includePrefix = true, bool includeName = true) const;
      virtual std::string getLabel() const;

    protected:

      KLFunction(const KLFile* klFile, JSONData data);

    private:
      
      std::string m_name;
      mutable std::string m_label;
      std::string m_returnType;
      std::string m_symbolName;
      std::vector<KLParameter*> m_params;
      KLCompoundStmt * m_body;
    };

  };

};


#endif // __ASTWrapper_KLFunction__
