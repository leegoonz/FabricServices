// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLLocation__
#define __ASTWrapper_KLLocation__

#include "KLDecl.h"

namespace FabricServices
{

  namespace ASTWrapper
  {

    class KLLocation
    {
      friend class KLDecl;

    public:

      virtual ~KLLocation();

      uint32_t getLine() const;
      uint32_t getColumn() const;

    protected:
      
      KLLocation(JSONData data);

    private:
      
      uint32_t m_line;
      uint32_t m_column;
    };

  };

};


#endif // __ASTWrapper_KLLocation__
