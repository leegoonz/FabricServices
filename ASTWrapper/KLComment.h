// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLComment__
#define __ASTWrapper_KLComment__

#include "KLDecl.h"

#include <string>
#include <map>
#include <vector>

namespace FabricServices
{

  namespace ASTWrapper
  {

    class KLComment : public KLDecl
    {
      friend class KLCommented;
      
    public:
      
      virtual bool isInternal() const;

    protected:

      KLComment(JSONData data);

      std::vector<std::string> m_lines;
      std::map<std::string, std::string> m_qualifiers;
    };

  };

};


#endif // __ASTWrapper_KLComment__
