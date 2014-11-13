// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __CodeCompletion_KLCodeCompletor__
#define __CodeCompletion_KLCodeCompletor__

#include "KLSyntaxHighlighter.h"
#include <ASTWrapper/KLASTManager.h>
#include <map>
#include <boost/regex.hpp>

namespace FabricServices
{

  namespace CodeCompletion
  {

    class KLCodeCompletor
    {
    public:

      KLCodeCompletor(const FabricCore::Client * client);
      KLCodeCompletor(ASTWrapper::KLASTManager * manager);
      KLCodeCompletor(KLSyntaxHighlighter * highlighter);
      virtual ~KLCodeCompletor();

      ASTWrapper::KLASTManager * getASTManager();
      KLSyntaxHighlighter * getHighlighter();

      void updateCurrentCodeAndFile(const std::string & code, const std::string & fileName);

      bool isCursorInsideCommentOrString(uint32_t cursor);
      bool isCursorInsideCommentOrString(uint32_t line, uint32_t column);
      // const ASTWrapper::KLStatement * getStatementFromCursor(uint32_t line, uint32_t column);

    private:

      void init();
      void lineAndColumnToCursor(uint32_t line, uint32_t column, uint32_t & cursor) const;
      void cursorToLineAndColumn(uint32_t cursor,  uint32_t & line, uint32_t & column) const;

      ASTWrapper::KLASTManager * m_manager;
      bool m_owningManager;
      KLSyntaxHighlighter * m_highlighter;
      bool m_owningHighlighter;

      std::string m_code;
      std::vector<std::string> m_lines;
      std::string m_fileName;

      boost::regex m_operatorExpr;
      boost::regex m_functionExpr;
      boost::regex m_ifExpr;
      boost::regex m_elseExpr;
      boost::regex m_forExpr;
      boost::regex m_whileExpr;
    };

  };

};


#endif // __CodeCompletion_KLCodeCompletor__
