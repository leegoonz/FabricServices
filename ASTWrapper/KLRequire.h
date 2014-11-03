// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLRequire__
#define __ASTWrapper_KLRequire__

#include "KLCommented.h"

#include <string>
#include <map>
#include <vector>

namespace FabricServices
{

  namespace ASTWrapper
  {

    class KLRequire : public KLCommented
    {
      friend class KLFile;

    public:

      virtual ~KLRequire();

      const std::string & getRequiredExtension() const;
      const std::string & getVersionRange() const;

    protected:
      
      KLRequire(JSONData data);

    private:
      
      std::string m_requiredExtension;
      std::string m_versionRange;
    };

  };

};


#endif // __ASTWrapper_KLRequire__
