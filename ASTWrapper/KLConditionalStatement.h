// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLConditionalStatement__
#define __ASTWrapper_KLConditionalStatement__

#include "KLStatement.h"

#include <string>

namespace FabricServices
{

  namespace ASTWrapper
  {
    class KLConditionalStatement : public KLStatement
    {
      friend class KLFunction;
      friend class KLStatement;

    public:

      virtual ~KLConditionalStatement() {}

      virtual KLStatement_Type getType() const { return KLStatement_Conditional; }
      const KLStatement * getTrueStatement() const;
      const KLStatement * getFalseStatement() const;

    protected:

      KLConditionalStatement(const KLFile* klFile, JSONData data, KLStatement * parent = NULL);
    };

  };

};


#endif // __ASTWrapper_KLConditionalStatement__
