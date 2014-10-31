// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLInterface__
#define __ASTWrapper_KLInterface__

#include "KLType.h"

#include <string>

namespace FabricServices
{

  namespace ASTWrapper
  {

    class KLInterface : public KLType
    {
    public:

      virtual ~KLInterface();

      virtual const char * getKLType() const;

    protected:

      KLInterface(JSONData data);
    };

  };

};


#endif // __ASTWrapper_KLInterface__
