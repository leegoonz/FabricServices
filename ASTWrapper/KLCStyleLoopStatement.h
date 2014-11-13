// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLCStyleLoopStatement__
#define __ASTWrapper_KLCStyleLoopStatement__

#include "KLStatement.h"

#include <string>

namespace FabricServices
{

  namespace ASTWrapper
  {
    class KLCStyleLoopStatement : public KLStatement
    {
      friend class KLFunction;
      friend class KLStatement;

    public:

      virtual ~KLCStyleLoopStatement() {}

      virtual KLStatement_Type getType() const { return KLStatement_CStyleLoop; }

    protected:

      KLCStyleLoopStatement(const KLFile* klFile, JSONData data, KLStatement * parent = NULL);
    };

  };

};


#endif // __ASTWrapper_KLCStyleLoopStatement__
