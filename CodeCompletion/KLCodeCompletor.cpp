// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLCodeCompletor.h"

#include <boost/algorithm/string.hpp>
#include <boost/range/algorithm/count.hpp>
#include <boost/range/algorithm/remove_if.hpp>

using namespace FabricServices;
using namespace FabricServices::CodeCompletion;

KLCodeCompletor::KLCodeCompletor(const FabricCore::Client * client)
{
  m_manager = new ASTWrapper::KLASTManager(client);
  m_owningManager = true;
  m_highlighter = new KLSyntaxHighlighter(m_manager);
  m_owningHighlighter = true;
  init();
}

KLCodeCompletor::KLCodeCompletor(ASTWrapper::KLASTManager * manager)
{
  m_manager = manager;
  m_owningManager = false;
  m_highlighter = new KLSyntaxHighlighter(m_manager);
  m_owningHighlighter = true;
  init();
}

KLCodeCompletor::KLCodeCompletor(KLSyntaxHighlighter * highlighter)
{
  m_manager = highlighter->getASTManager();
  m_owningManager = false;
  m_highlighter = highlighter;
  m_owningHighlighter = false;
  init();
}

KLCodeCompletor::~KLCodeCompletor()
{
  if(m_owningManager && m_manager)
    delete(m_manager);
}

void KLCodeCompletor::init()
{
  m_operatorExpr = boost::regex("operator[^\\(\\){}]*\\([^\\)]*\\)");
  // m_functionExpr = boost::regex("function[^\\(\\){}]*\\([^\\)]*\\)");
  // m_ifExpr = boost::regex("if[^{};]*\\([^{};]*\\)[\\{;]");
  // m_elseExpr = boost::regex("else[^{}]*[\\(;]");
  // m_forExpr = boost::regex("for[^{}]*\\(.*\\)[\\(;]");
  // m_forExpr = boost::regex("");
  // m_whileExpr = boost::regex("");
}

ASTWrapper::KLASTManager * KLCodeCompletor::getASTManager()
{
  return m_manager;
}

KLSyntaxHighlighter * KLCodeCompletor::getHighlighter()
{
  return m_highlighter;
}

void KLCodeCompletor::updateCurrentCodeAndFile(const std::string & code, const std::string & fileName)
{
  m_code = code;
  m_code.erase(boost::remove_if(m_code, boost::is_any_of("\r")), m_code.end());
  boost::split(m_lines, m_code, boost::is_any_of("\n"));

  m_fileName = fileName;
  m_highlighter->updateRulesFromCode(code, fileName);

}

bool KLCodeCompletor::isCursorInsideCommentOrString(uint32_t cursor)
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

bool KLCodeCompletor::isCursorInsideCommentOrString(uint32_t line, uint32_t column)
{
  uint32_t cursor = 0;
  lineAndColumnToCursor(line, column, cursor);
  return isCursorInsideCommentOrString(cursor);
}

// const ASTWrapper::KLStatement * KLCodeCompletor::getStatementFromCursor(uint32_t cursor)
// {
//   if(cursor >= m_code.length())
//     return NULL;

//   const ASTWrapper::KLExtension * extension = m_manager->getExtension(m_fileName.c_str());
//   if(!extension)
//     return NULL;

//   uint32_t c = cursor;

//   boost::match_results<std::string::const_iterator> what;
//   boost::match_flag_type flags = boost::match_default;
//   std::string::const_iterator s = m_code.begin();
//   std::string::const_iterator e = m_code.end();
//   if(boost::regex_search(s,e,what,m_operatorExpr,flags))
//   {
//     printf("pos %d length %d\n", (int)what.position(), (int)what.length());
//   }
  
//   return NULL;  
// }

void KLCodeCompletor::lineAndColumnToCursor(uint32_t line, uint32_t column, uint32_t & cursor) const
{
  cursor = 0;
  for(uint32_t l=0; l<line; l++)
  {
    if(l >= m_lines.size())
      return;
    cursor += m_lines[l].length() + 1;
  }
  cursor += column;
}

void KLCodeCompletor::cursorToLineAndColumn(uint32_t cursor,  uint32_t & line, uint32_t & column) const
{
  line = 0;
  column = 0;
  if(m_lines.size() == 0)
    return;

  uint32_t sum = cursor;
  for(line=0; line<m_lines.size(); line++)
  {
    if(sum <= m_lines[line].length())
    {
      column = sum;
      return;
    }
    sum -= m_lines[line].length() + 1;
  }

  column = m_lines[m_lines.size() - 1].length();
}
