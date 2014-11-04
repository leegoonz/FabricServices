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
      friend class KLFile;

    public:

      virtual ~KLInterface();

      virtual const char * getKLType() const;
      virtual std::vector<const KLType*> getParents() const;

    protected:

      KLInterface(const KLFile* klFile, JSONData data);
    };

  };

};


#endif // __ASTWrapper_KLInterface__
