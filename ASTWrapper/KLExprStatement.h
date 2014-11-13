// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLExprStatement__
#define __ASTWrapper_KLExprStatement__

#include "KLStatement.h"

#include <string>

namespace FabricServices
{

  namespace ASTWrapper
  {
    class KLExprStatement : public KLStatement
    {
      friend class KLFunction;
      friend class KLStatement;

    public:

      virtual ~KLExprStatement() {}

      virtual KLStatement_Type getType() const { return KLStatement_Expr; }

    protected:

      KLExprStatement(const KLFile* klFile, JSONData data, KLStatement * parent = NULL);
    };

  };

};


#endif // __ASTWrapper_KLExprStatement__
