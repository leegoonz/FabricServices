// Copyright 2010-2013 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLDecl__
#define __ASTWrapper_KLDecl__

#include <FabricCore.h>

namespace FabricCore
{

  namespace ASTWrapper
  {

    class KLDecl
    {
    public:
      KLDecl(const FabricCore::Variant & data);

    private:
      FabricCore::Variant data;
    };

  };

};


#endif // __ASTWrapper_KLDecl__
