// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __CodeCompletion_KLCodeAssistant__
#define __CodeCompletion_KLCodeAssistant__

#include "KLSyntaxHighlighter.h"
#include "KLVariable.h"
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
      void setASTManager(ASTWrapper::KLASTManager * manager);

      KLSyntaxHighlighter * getHighlighter();
      const ASTWrapper::KLFile * getKLFile();

      void updateCurrentKLFile(const ASTWrapper::KLFile * file);
      void updateCurrentCodeAndFile(const std::string & code, const std::string & fileName);

      void lineAndColumnToCursor(uint32_t line, uint32_t column, uint32_t & cursor) const;
      void cursorToLineAndColumn(uint32_t cursor,  uint32_t & line, uint32_t & column) const;

      bool isCursorInsideCommentOrString(uint32_t cursor) const;
      bool isCursorInsideCommentOrString(uint32_t line, uint32_t column) const;

      const ASTWrapper::KLStatement * getStatementAtCursor(uint32_t cursor) const;
      const ASTWrapper::KLStatement * getStatementAtCursor(uint32_t line, uint32_t column) const;
      std::string getCodeForStatement(const ASTWrapper::KLStatement * statement) const;

      std::string getWordAtCursor(uint32_t cursor) const;
      std::string getWordAtCursor(uint32_t line, uint32_t column) const;

      std::vector<KLVariable> getVariablesAtCursor(uint32_t cursor) const;
      std::vector<KLVariable> getVariablesAtCursor(uint32_t line, uint32_t column) const;

      const ASTWrapper::KLType * getTypeAtCursor(uint32_t cursor) const;
      const ASTWrapper::KLType * getTypeAtCursor(uint32_t line, uint32_t column) const;

    private:

      void init();
      const char * resolveAliases(const char * name) const;

      ASTWrapper::KLASTManager * m_manager;
      bool m_owningManager;
      KLSyntaxHighlighter * m_highlighter;
      bool m_owningHighlighter;

      std::string m_code;
      std::vector<std::string> m_lines;
      std::string m_fileName;
      const ASTWrapper::KLFile * m_file;
    };

  };

};


#endif // __CodeCompletion_KLCodeAssistant__
