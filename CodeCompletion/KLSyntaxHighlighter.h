// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __CodeCompletion_KLSyntaxHighlighter__
#define __CodeCompletion_KLSyntaxHighlighter__

#include "SyntaxHighlighter.h"
#include <ASTWrapper/KLASTManager.h>

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

      virtual std::vector<Format> getHighlightFormats(const std::string & text, const std::string & fileName = "") const;

    private:

      void initRules();

      ASTWrapper::KLASTManager * m_manager;
      bool m_owningManager;
    };

  };

};


#endif // __CodeCompletion_KLSyntaxHighlighter__
