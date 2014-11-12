// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __CodeCompletion_KLCodeCompletor__
#define __CodeCompletion_KLCodeCompletor__

#include <ASTWrapper/KLASTManager.h>
#include <map>

/*
<andrew> you can just add an appendJSONMembers to the relevant things in the AST/ folder
<andrew> like VarDecl or VarDeclStatement, whichever one it is
<helge> ok. thanks.
<andrew> you might need to add one to CompoundStatement as well
<andrew> since that's the function body
<helge> ah ok
<andrew> so it will need to iterate over each sub-statement
<andrew> and call appendJSONMembers on those
<andrew> just check how it's implemented for the others, should be fairly straightforward
<helge> ok. I'll see if I can get it to work - I'll have you review it.
<helge> thanks.
*/

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
