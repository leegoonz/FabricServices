// Copyright 2010-2013 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLComment__
#define __ASTWrapper_KLComment__

#include <FabricCore.h>
#include "KLDecl.h"

namespace FabricCore
{

  namespace ASTWrapper
  {

    class KLComment : public KLDecl
    {
    public:
      KLComment(const FabricCore::Variant & data);
    };

  };

};


#endif // __ASTWrapper_KLComment__
