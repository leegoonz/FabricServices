// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLMember__
#define __ASTWrapper_KLMember__

#include "KLCommented.h"

#include <string>

namespace FabricServices
{

  namespace ASTWrapper
  {

    class KLMember : public KLCommented
    {
    public:

      virtual ~KLMember();

      const std::string & getName() const;
      const std::string & getType() const;

    protected:

      KLMember(JSONData data);

    private:
      
      std::string m_name;
      std::string m_type;
    };

  };

};


#endif // __ASTWrapper_KLMember__
