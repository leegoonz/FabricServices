// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLCommented__
#define __ASTWrapper_KLCommented__

#include <FabricCore.h>
#include "KLDecl.h"

#include <string>

namespace FabricCore
{

  namespace ASTWrapper
  {

    class KLCommented : public KLDecl
    {
    public:

      typedef boost::smart_ptr<KLCommented> Ptr;

      KLCommented(const FabricCore::Variant * data);

      KLComment::Ptr getComments() const;


    private:
      KLComment::Ptr m_comments;
    };

  };

};


#endif // __ASTWrapper_KLCommented__
