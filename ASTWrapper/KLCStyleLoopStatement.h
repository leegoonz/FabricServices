// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

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

      virtual KLDeclType getDeclType() const;
      virtual bool isOfDeclType(KLDeclType type) const;

    protected:

      KLCStyleLoopStatement(const KLFile* klFile, JSONData data, KLStatement * parent = NULL);
    };

  };

};


#endif // __ASTWrapper_KLCStyleLoopStatement__
