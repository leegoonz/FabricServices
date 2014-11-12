// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __CodeCompletion_KLCodeCompletor__
#define __CodeCompletion_KLCodeCompletor__

#include <ASTWrapper/KLASTManager.h>
#include <map>

namespace FabricServices
{

  namespace CodeCompletion
  {

    class KLCodeCompletor
    {
    public:

      KLCodeCompletor(const FabricCore::Client * client);
      KLCodeCompletor(ASTWrapper::KLASTManager * manager);
      virtual ~KLCodeCompletor();

    private:

      ASTWrapper::KLASTManager * m_manager;
      bool m_owningManager;
    };

  };

};


#endif // __CodeCompletion_KLCodeCompletor__
