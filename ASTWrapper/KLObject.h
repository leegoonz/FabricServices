// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLObject__
#define __ASTWrapper_KLObject__

#include "KLType.h"

#include <string>

namespace FabricServices
{

  namespace ASTWrapper
  {

    class KLObject : public KLType
    {
    public:

      virtual ~KLObject();

      virtual const char * getKLType() const;
      virtual std::vector<const KLType*> getParents() const = 0;

    protected:

      KLObject(JSONData data);

    private:
      std::vector<std::string> m_parentsAndInterfaces;
    };

  };

};


#endif // __ASTWrapper_KLObject__
