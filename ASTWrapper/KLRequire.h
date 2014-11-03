// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLRequire__
#define __ASTWrapper_KLRequire__

#include "KLDecl.h"

#include <string>
#include <map>
#include <vector>

namespace FabricServices
{

  namespace ASTWrapper
  {

    class KLRequire : public KLDecl
    {
    public:

      virtual ~KLRequire();

      const std::string & getRequiredExtension() const;

    protected:
      
      KLRequire(JSONData data);

    private:
      
      std::string m_requiredExtension;
    };

  };

};


#endif // __ASTWrapper_KLRequire__
