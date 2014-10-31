// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLConstant__
#define __ASTWrapper_KLConstant__

#include <FabricCore.h>
#include "KLDecl.h"

#include <string>
#include <map>
#include <vector>

namespace FabricCore
{

  namespace ASTWrapper
  {

    class KLConstant : public KLDecl
    {
    public:

      typedef boost::smart_ptr<KLConstant> Ptr;

      KLConstant(const FabricCore::Variant * data);

      const std::string & getName() const;
      const std::string & getType() const;

    private:
      std::string m_name;
      std::string m_type;
    };

  };

};


#endif // __ASTWrapper_KLConstant__
