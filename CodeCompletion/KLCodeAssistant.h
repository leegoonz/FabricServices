// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __CodeCompletion_KLCodeAssistant__
#define __CodeCompletion_KLCodeAssistant__

#include "KLSyntaxHighlighter.h"
#include <ASTWrapper/KLASTManager.h>
#include <map>
#include <boost/regex.hpp>

namespace FabricServices
{

  namespace CodeCompletion
  {

    class KLCodeAssistant
    {
    public:

      KLCodeAssistant(const FabricCore::Client * client);
      KLCodeAssistant(ASTWrapper::KLASTManager * manager);
      KLCodeAssistant(KLSyntaxHighlighter * highlighter);
      virtual ~KLCodeAssistant();

      ASTWrapper::KLASTManager * getASTManager();
      KLSyntaxHighlighter * getHighlighter();

      void updateCurrentCodeAndFile(const std::string & code, const std::string & fileName);

      void lineAndColumnToCursor(uint32_t line, uint32_t column, uint32_t & cursor) const;
      void cursorToLineAndColumn(uint32_t cursor,  uint32_t & line, uint32_t & column) const;

      bool isCursorInsideCommentOrString(uint32_t cursor) const;
      bool isCursorInsideCommentOrString(uint32_t line, uint32_t column) const;
      const ASTWrapper::KLStatement * getStatementFromCursor(uint32_t cursor) const;
      const ASTWrapper::KLStatement * getStatementFromCursor(uint32_t line, uint32_t column) const;
      std::string getCodeForStatement(const ASTWrapper::KLStatement * statement) const;

    private:

      void init();

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


#endif // __CodeCompletion_KLCodeAssistant__
