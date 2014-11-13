// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLStatementSearch__
#define __ASTWrapper_KLStatementSearch__

namespace FabricServices
{

  namespace ASTWrapper
  {
    // forward decl
    class KLStatement;

    class KLStatementSearch
    {
      virtual const KLStatement * getStatementAtCursor(uint32_t line, uint32_t column) const = 0;
    };
    
  };

};

#endif // __ASTWrapper_KLStatementSearch__
