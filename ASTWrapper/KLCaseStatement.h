// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLCaseStatement__
#define __ASTWrapper_KLCaseStatement__

#include "KLStatement.h"

#include <string>

namespace FabricServices
{

  namespace ASTWrapper
  {
    class KLCaseStatement : public KLStatement
    {
      friend class KLFunction;
      friend class KLStatement;

    public:

      virtual ~KLCaseStatement() {}

      virtual KLStatement_Type getType() const { return KLStatement_Case; }

    protected:

      KLCaseStatement(const KLFile* klFile, JSONData data, KLStatement * parent = NULL);
    };

  };

};


#endif // __ASTWrapper_KLCaseStatement__
