// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLFunctionBody__
#define __ASTWrapper_KLFunctionBody__

#include "KLDecl.h"
#include "KLVariable.h"

#include <string>

namespace FabricServices
{

  namespace ASTWrapper
  {

    class KLFunctionBody : public KLDecl
    {
      friend class KLFunction;

    public:

      virtual ~KLFunctionBody();

      virtual bool isInternal() const { return false; }

      virtual uint32_t getVariableCount() const;
      virtual const KLVariable * getVariable(uint32_t index) const;

    protected:

      KLFunctionBody(const KLFile* klFile, JSONData data);

    private:

      void parseStatement(JSONData data);
      void parseCompoundStatement(JSONData data);
      void parseSwitchStatement(JSONData data);
      void parseConditionalStatement(JSONData data);
      void parseLoopStatement(JSONData data);
      
      std::vector<KLVariable*> m_variables;
    };

  };

};


#endif // __ASTWrapper_KLFunctionBody__
