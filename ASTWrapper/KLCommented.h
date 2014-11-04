// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLCommented__
#define __ASTWrapper_KLCommented__

#include "KLDecl.h"
#include "KLComment.h"

#include <string>

namespace FabricServices
{

  namespace ASTWrapper
  {

    class KLCommented : public KLDecl
    {
    public:

      virtual ~KLCommented();

      virtual bool isInternal() const;
      virtual const KLComment * getComments() const;

    protected:

      KLCommented(const KLFile* klFile, JSONData data);

    private:
      
      KLComment * m_comments;
    };

  };

};


#endif // __ASTWrapper_KLCommented__
