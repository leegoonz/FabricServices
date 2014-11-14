// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLCodeAssistant.h"

#include <boost/algorithm/string.hpp>
#include <boost/range/algorithm/count.hpp>
#include <boost/range/algorithm/remove_if.hpp>

using namespace FabricServices::ASTWrapper;
using namespace FabricServices::CodeCompletion;

KLCodeAssistant::KLCodeAssistant(const FabricCore::Client * client)
{
  m_manager = new KLASTManager(client);
  m_owningManager = true;
  m_highlighter = new KLSyntaxHighlighter(m_manager);
  m_owningHighlighter = true;
  init();
}

KLCodeAssistant::KLCodeAssistant(KLASTManager * manager)
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
  m_file = NULL;
}

KLASTManager * KLCodeAssistant::getASTManager()
{
  return m_manager;
}

void KLCodeAssistant::setASTManager(KLASTManager * manager)
{
  if(m_owningManager && m_manager)
    delete(m_manager);
  m_manager = manager;
  m_owningManager = false;
  if(m_owningHighlighter && m_highlighter)
    m_highlighter->setASTManager(manager);
}

KLSyntaxHighlighter * KLCodeAssistant::getHighlighter()
{
  return m_highlighter;
}

const KLFile * KLCodeAssistant::getKLFile()
{
  return m_file;
}

void KLCodeAssistant::updateCurrentKLFile(const KLFile * file)
{
  m_file = file;
  m_fileName = m_file->getFileName();
  m_code = m_file->getKLCode();
  m_code.erase(boost::remove_if(m_code, boost::is_any_of("\r")), m_code.end());
  boost::split(m_lines, m_code, boost::is_any_of("\n"));
}

void KLCodeAssistant::updateCurrentCodeAndFile(const std::string & code, const std::string & fileName, bool updateAST)
{
  m_code = code;
  m_code.erase(boost::remove_if(m_code, boost::is_any_of("\r")), m_code.end());
  boost::split(m_lines, m_code, boost::is_any_of("\n"));

  m_fileName = fileName;

  if(updateAST)
  {
    m_highlighter->updateRulesFromCode(code, fileName);
    m_file = NULL;

    const KLExtension * extension = m_manager->getExtension(m_fileName.c_str());
    if(extension)
    {
      std::vector<const KLFile*> files = extension->getFiles();
      if(files.size() > 0)
        m_file = files[0];
    }
  }
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

const KLStatement * KLCodeAssistant::getStatementAtCursor(uint32_t cursor) const
{
  uint32_t line = 0;
  uint32_t column = 0;
  cursorToLineAndColumn(cursor, line, column);
  return getStatementAtCursor(line, column);
}

const KLStatement * KLCodeAssistant::getStatementAtCursor(uint32_t line, uint32_t column) const
{
  if(!m_file)
    return NULL;
  return m_file->getStatementAtCursor(line, column);
}

std::string KLCodeAssistant::getCodeForStatement(const KLStatement * statement) const
{
  uint32_t start, end;
  lineAndColumnToCursor(statement->getLocation()->getLine(), statement->getLocation()->getColumn(), start);
  lineAndColumnToCursor(statement->getLocation()->getEndLine(), statement->getLocation()->getEndColumn(), end);
  return m_code.substr(start, end - start);
}

std::string KLCodeAssistant::getWordAtCursor(uint32_t cursor) const
{
  uint32_t line, column;
  cursorToLineAndColumn(cursor, line, column);
  return getWordAtCursor(line, column);
}

#define isWordChar(c) (isalnum(c) || (c == '_'))

std::string KLCodeAssistant::getWordAtCursor(uint32_t line, uint32_t column) const
{
  if(line > m_lines.size() || line == 0)
    return "";

  const std::string & l = m_lines[line-1];
  if(column > l.length() || column == 0)
    return "";

  uint32_t s = column - 1;
  uint32_t e = column - 1;

  while(s > 0)
  {
    if(!isWordChar(l[s-1]))
      break;
    s--;
  }
  while(e < l.length()-1)
  {
    if(!isWordChar(l[e+1]))
      break;
    e++;
  }

  if(isWordChar(l[s]) && isWordChar(l[e]))
    return l.substr(s, e - s + 1);  

  return "";
}

std::vector<KLVariable> KLCodeAssistant::getVariablesAtCursor(uint32_t cursor) const
{
  uint32_t line, column;
  cursorToLineAndColumn(cursor, line, column);
  return getVariablesAtCursor(line, column);
}

std::vector<KLVariable> KLCodeAssistant::getVariablesAtCursor(uint32_t line, uint32_t column) const
{
  std::vector<KLVariable> result;
  const KLStatement * statement = getStatementAtCursor(line, column);
  if(statement)
  {
    if(statement->isOfDeclType(KLDeclType_Function))
      statement = ((KLFunction*)statement)->getBody();
  }
  if(statement)
  {
    std::vector<const KLStatement *> varDecls = statement->getAllChildrenOfType(KLDeclType_VarDeclStatement, false, true);
    for(size_t i=0;i<varDecls.size();i++)
    {
      const KLVarDeclStatement * varDecl = (const KLVarDeclStatement *)varDecls[i];
      for(uint32_t j=0;j<varDecl->getCount();j++)
      {
        result.push_back(KLVariable(varDecl->getName(j), varDecl->getBaseType(), varDecl->getArrayModifier(j)));
      }
    }

    statement = statement->getTop();

    if(statement->isOfDeclType(KLDeclType_Function))
    {
      KLFunction * function = (KLFunction *)statement;
      for(uint32_t i=0;i<function->getParameterCount();i++)
      {
        const KLParameter * param = function->getParameter(i);
        result.push_back(KLVariable(param->getName(), param->getType()));
      }        
    }
  }

  return result;
}

const KLDecl * KLCodeAssistant::getDeclAtCursor(uint32_t cursor) const
{
  uint32_t line, column;
  cursorToLineAndColumn(cursor, line, column);
  return getDeclAtCursor(line, column);
}

const KLDecl * KLCodeAssistant::getDeclAtCursor(uint32_t line, uint32_t column) const
{
  if(line > m_lines.size() || line == 0)
    return NULL;

  const std::string & l = m_lines[line-1];
  if(column == 0)
    return NULL;
  if(column > l.length())
    column = l.length();

  std::vector<std::string> delegates;
  uint32_t braces = 0;
  uint32_t brackets = 0;
  uint32_t singleQuotes = 0;
  uint32_t doubleQuotes = 0;

  int i = column - 1;

  bool resolved = false;
  std::string word;
  while(i >= 0 && !resolved)
  {
    char c = l[i];
    if(c == ')')
    {
      braces++;
    }    
    else if(c == '(')
    {
      if(braces > 0)
        braces--;
    }    
    else if(c == ']')
    {
      brackets++;
    }    
    else if(c == '[')
    {
      if(brackets > 0)
        brackets--;
    }    
    else if(c == '\'' && doubleQuotes == 0)
    {
      singleQuotes = singleQuotes == 1 ? 0 : 1;
    }    
    else if(c == '\'' && singleQuotes == 0)
    {
      doubleQuotes = doubleQuotes == 1 ? 0 : 1;
    }    
    else if(braces == 0 && brackets == 0 && singleQuotes == 0 && doubleQuotes == 0 && (isalnum(c) || c == '_'))
    {
      word = c + word;
    }
    else if(c == '.')
    {
      if(word.length() > 0)
      {
        delegates.insert(delegates.begin(), word);
        word = "";
      }
    }
    else if(c == ' ' || c == '\t')
    {
      // pass
    }
    else if(braces == 0 && brackets == 0 && singleQuotes == 0 && doubleQuotes == 0)
    {
      resolved = true;
    }
    i--;
  }

  const KLType * type = NULL;
  if(word.length() > 0)
  {
    // try all variables
    if(type == NULL)
    {
      std::vector<KLVariable> vars = getVariablesAtCursor(line, i+1);
      for(size_t i=0;i<vars.size();i++)
      {
        if(vars[i].getName() == word)
        {
          type = m_manager->getKLTypeByName(resolveAliases(vars[i].getBaseType().c_str()), m_file);
          if(type)
            break;
        }
      }
    }

    // maybe this is a type itself
    if(type == NULL)
    {
      type = m_manager->getKLTypeByName(resolveAliases(word.c_str()), m_file);
    }

    // maybe this is a function
    if(type == NULL)
    {
      std::vector<const KLFunction*> functions = m_manager->getFunctions();
      for(size_t i=0;i<functions.size();i++)
      {
        if(functions[i]->getName() == word)
        {
          if(delegates.size() == 0)
            return functions[i];

          KLTypeDesc returnType(functions[i]->getReturnType());
          type = m_manager->getKLTypeByName(resolveAliases(returnType.getBaseType().c_str()), m_file);
          if(type)
            break;
        }
      }
    }
  }

  if(type)
  {
    for(size_t i=0;i<delegates.size();i++)
    {
      bool found = false;
      std::vector<const KLMethod*> methods = type->getMethods(true);
      for(size_t j=0;j<methods.size();j++)
      {
        const KLMethod * method = methods[j];
        if(method == NULL)
          continue;
        if(method->getName() != delegates[i])
          continue;

        if(i == delegates.size()-1)
          return method;

        KLTypeDesc returnType(method->getReturnType());
        type = m_manager->getKLTypeByName(resolveAliases(returnType.getBaseType().c_str()), m_file);
        if(type == NULL)
          return NULL;
        found = true;
        break;
      }

      if(!found)
      {
        if(type->getKLType() != "interface")
        {
          const KLStruct * castType = (const KLStruct *)type;
          const KLMember * member = castType->getMember(delegates[i].c_str(), true);
          if(member)
          {
            KLTypeDesc memberType(member->getType());
            type = m_manager->getKLTypeByName(memberType.getBaseType().c_str(), m_file);
            if(type == NULL)
              return NULL;
          }
        }
      }
    }
  }

  return type;
}

const KLType * KLCodeAssistant::getTypeAtCursor(uint32_t cursor) const
{
  uint32_t line, column;
  cursorToLineAndColumn(cursor, line, column);
  return getTypeAtCursor(line, column);
}

const KLType * KLCodeAssistant::getTypeAtCursor(uint32_t line, uint32_t column) const
{
  const KLDecl * decl = getDeclAtCursor(line, column);
  if(decl)
  {
    if(decl->isOfDeclType(KLDeclType_Type))
    {
      return (const KLType *)decl;
    }
    else if(decl->isOfDeclType(KLDeclType_Function))
    {
      KLTypeDesc returnType(((const KLFunction*)decl)->getReturnType());
      return m_manager->getKLTypeByName(resolveAliases(returnType.getBaseType().c_str()), m_file);
    }
  }
  return NULL;
}

const char * KLCodeAssistant::resolveAliases(const char * name) const
{
  std::vector<const KLAlias*> aliases = m_manager->getAliases();
  const char * result = name;

  bool found = true;
  while(found)
  {
    found = false;
    for(size_t i=0;i<aliases.size();i++)
    {
      if(aliases[i]->getNewUserName() == result)
      {
        result = aliases[i]->getOldUserName().c_str();
        found = true;
        break;
      }
    }
  }
  
  return result;
}


