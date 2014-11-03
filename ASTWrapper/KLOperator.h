// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLOperator__
#define __ASTWrapper_KLOperator__

#include "KLFunction.h"

#include <string>

namespace FabricServices
{

  namespace ASTWrapper
  {

    class KLOperator : public KLFunction
    {
    public:

      virtual ~KLOperator();
      virtual const char * getKLType() const;

    protected:

      KLOperator(JSONData data);
    };

  };

};


#endif // __ASTWrapper_KLOperator__
