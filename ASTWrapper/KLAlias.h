// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLAlias__
#define __ASTWrapper_KLAlias__

#include "KLCommented.h"

#include <string>
#include <map>
#include <vector>

namespace FabricServices
{

  namespace ASTWrapper
  {

    class KLAlias : public KLCommented
    {
      friend class KLFile;

    public:

      virtual ~KLAlias();

      const std::string & getNewUserName() const;
      const std::string & getOldUserName() const;

    protected:
      
      KLAlias(const KLFile* klFile, JSONData data);

    private:
      
      std::string m_newUserName;
      std::string m_oldUserName;
    };

  };

};


#endif // __ASTWrapper_KLAlias__
