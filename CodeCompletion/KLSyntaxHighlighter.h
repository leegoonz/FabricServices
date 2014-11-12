// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __CodeCompletion_KLSyntaxHighlighter__
#define __CodeCompletion_KLSyntaxHighlighter__

#include "SyntaxHighlighter.h"
#include <ASTWrapper/KLASTManager.h>
#include <map>

namespace FabricServices
{

  namespace CodeCompletion
  {

    class KLSyntaxHighlighter : public SyntaxHighlighter
    {
    public:

      KLSyntaxHighlighter(const FabricCore::Client * client);
      KLSyntaxHighlighter(ASTWrapper::KLASTManager * manager);
      virtual ~KLSyntaxHighlighter();

      virtual void updateRulesFromCode(const std::string & code, const std::string & fileName);

    private:

      void initRules();

      ASTWrapper::KLASTManager * m_manager;
      bool m_owningManager;
      std::map<std::string, HighlightRule*> m_constantRules;
      std::map<std::string, HighlightRule*> m_typeRules;
    };

  };

};


#endif // __CodeCompletion_KLSyntaxHighlighter__
