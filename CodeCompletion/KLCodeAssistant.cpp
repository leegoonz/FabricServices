// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLCodeAssistant.h"

#include <boost/algorithm/string.hpp>
#include <boost/range/algorithm/count.hpp>
#include <boost/range/algorithm/remove_if.hpp>

using namespace FabricServices;
using namespace FabricServices::CodeCompletion;

KLCodeAssistant::KLCodeAssistant(const FabricCore::Client * client)
{
  m_manager = new ASTWrapper::KLASTManager(client);
  m_owningManager = true;
  m_highlighter = new KLSyntaxHighlighter(m_manager);
  m_owningHighlighter = true;
  init();
}

KLCodeAssistant::KLCodeAssistant(ASTWrapper::KLASTManager * manager)
{
  m_manager = manager;
  m_owningManager = false;
  m_highlighter = new KLSyntaxHighlighter(m_manager);
  m_owningHighlighter = true;
  init();
}

KLCodeAssistant::KLCodeAssistant(KLSyntaxHighlighter * highlighter)
{
  m_manager = highlighter->getASTManager();
  m_owningManager = false;
  m_highlighter = highlighter;
  m_owningHighlighter = false;
  init();
}

KLCodeAssistant::~KLCodeAssistant()
{
  if(m_owningManager && m_manager)
    delete(m_manager);
}

void KLCodeAssistant::init()
{
  m_operatorExpr = boost::regex("operator[^\\(\\){}]*\\([^\\)]*\\)");
  // m_functionExpr = boost::regex("function[^\\(\\){}]*\\([^\\)]*\\)");
  // m_ifExpr = boost::regex("if[^{};]*\\([^{};]*\\)[\\{;]");
  // m_elseExpr = boost::regex("else[^{}]*[\\(;]");
  // m_forExpr = boost::regex("for[^{}]*\\(.*\\)[\\(;]");
  // m_forExpr = boost::regex("");
  // m_whileExpr = boost::regex("");
}

ASTWrapper::KLASTManager * KLCodeAssistant::getASTManager()
{
  return m_manager;
}

KLSyntaxHighlighter * KLCodeAssistant::getHighlighter()
{
  return m_highlighter;
}

void KLCodeAssistant::updateCurrentCodeAndFile(const std::string & code, const std::string & fileName)
{
  m_code = code;
  m_code.erase(boost::remove_if(m_code, boost::is_any_of("\r")), m_code.end());
  boost::split(m_lines, m_code, boost::is_any_of("\n"));

  m_fileName = fileName;
  m_highlighter->updateRulesFromCode(code, fileName);

}

void KLCodeAssistant::lineAndColumnToCursor(uint32_t line, uint32_t column, uint32_t & cursor) const
{
  cursor = 0;
  for(uint32_t l=1; l<line; l++)
  {
    if(l >= m_lines.size())
      return;
    cursor += m_lines[l-1].length() + 1;
  }
  cursor += column - 1;
}

void KLCodeAssistant::cursorToLineAndColumn(uint32_t cursor,  uint32_t & line, uint32_t & column) const
{
  line = 0;
  column = 0;
  if(m_lines.size() == 0)
    return;

  uint32_t sum = cursor;
  for(line=1; line<=m_lines.size(); line++)
  {
    if(sum <= m_lines[line-1].length())
    {
      column = sum + 1;
      return;
    }
    sum -= m_lines[line-1].length() + 1;
  }

  column = m_lines[m_lines.size() - 1].length() + 1;
}

bool KLCodeAssistant::isCursorInsideCommentOrString(uint32_t cursor) const
{
  if(cursor >= m_code.length())
    return false;

  const std::vector<SyntaxHighlighter::Format> & formats = m_highlighter->getHighlightFormats(m_code);
  for(size_t i=0;i<formats.size();i++)
  {
    if(formats[i].type == HighlightRuleType_Comment || formats[i].type == HighlightRuleType_String)
    {
      if(formats[i].start <= cursor && formats[i].start + formats[i].length >= cursor)
        return true;
    }
  }

  return false;
}

bool KLCodeAssistant::isCursorInsideCommentOrString(uint32_t line, uint32_t column) const
{
  uint32_t cursor = 0;
  lineAndColumnToCursor(line, column, cursor);
  return isCursorInsideCommentOrString(cursor);
}

const ASTWrapper::KLStatement * KLCodeAssistant::getStatementFromCursor(uint32_t cursor) const
{
  uint32_t line = 0;
  uint32_t column = 0;
  cursorToLineAndColumn(cursor, line, column);
  return getStatementFromCursor(line, column);
}

const ASTWrapper::KLStatement * KLCodeAssistant::getStatementFromCursor(uint32_t line, uint32_t column) const
{
  const ASTWrapper::KLExtension * extension = m_manager->getExtension(m_fileName.c_str());
  if(!extension)
    return NULL;
  std::vector<const ASTWrapper::KLFile*> files = extension->getFiles();
  if(files.size() == 0)
    return NULL;

  return files[0]->getStatementFromCursor(line, column);
}

std::string KLCodeAssistant::getCodeForStatement(const ASTWrapper::KLStatement * statement) const
{
  uint32_t start, end;
  lineAndColumnToCursor(statement->getLocation()->getLine(), statement->getLocation()->getColumn(), start);
  lineAndColumnToCursor(statement->getLocation()->getEndLine(), statement->getLocation()->getEndColumn(), end);
  return m_code.substr(start, end - start);
}
