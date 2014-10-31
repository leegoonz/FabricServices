// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLComment__
#define __ASTWrapper_KLComment__

#include <FabricCore.h>
#include "KLDecl.h"

#include <string>
#include <map>
#include <vector>

namespace FabricCore
{

  namespace ASTWrapper
  {

    class KLComment : public KLDecl
    {
    public:

      typedef boost::smart_ptr<KLComment> Ptr;
      
      KLComment(const FabricCore::Variant * data);

      virtual bool isInternal() const;

    private:
      std::vector<std::string> m_lines;
      std::map<std::string, std::string> m_qualifiers;
    };

  };

};


#endif // __ASTWrapper_KLComment__
