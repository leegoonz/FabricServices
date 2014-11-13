// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLSwitchStatement__
#define __ASTWrapper_KLSwitchStatement__

#include "KLStatement.h"

#include <string>

namespace FabricServices
{

  namespace ASTWrapper
  {
    class KLSwitchStatement : public KLStatement
    {
      friend class KLFunction;
      friend class KLStatement;

    public:

      virtual ~KLSwitchStatement() {}

      virtual KLStatement_Type getType() const { return KLStatement_Switch; }

    protected:

      KLSwitchStatement(const KLFile* klFile, JSONData data, KLStatement * parent = NULL);
    };

  };

};


#endif // __ASTWrapper_KLSwitchStatement__
