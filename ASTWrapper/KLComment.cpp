// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLComment.h"

#include <boost/algorithm/string.hpp>
#include <boost/range/algorithm/count.hpp>
#include <boost/range/algorithm/remove_if.hpp>
#include <boost/regex.hpp>

using namespace FabricServices::ASTWrapper;

KLComment::KLComment(const KLFile* klFile, JSONData data)
: KLDecl(klFile, data)
{
  gatherDoxygenContent();
}

KLComment::~KLComment()
{
}

KLDeclType KLComment::getDeclType() const
{
  return KLDeclType_Comment;
}

bool KLComment::isOfDeclType(KLDeclType type) const
{
  return type == KLDeclType_Comment;
}

bool KLComment::isInternal() const
{
  return true;
}

void KLComment::gatherDoxygenContent() const
{
  if(m_content.size() > 0)
    return;

  bool inBlock = false;
  for(uint32_t i=0;i<getArraySize();i++)
  {
    std::vector<std::string> lines;
    const char * content = getStringArrayElement(i);
    if(!content)
      continue;

    boost::split(lines, content, boost::is_any_of("\n"));
    for(uint32_t j=0;j<lines.size();j++)
    {
      std::string l0 = lines[j];
      std::string l1 = lines[j];
      boost::trim_if(l0, boost::is_any_of(" \t\n\r"));
      boost::trim_if(l1, boost::is_any_of("/*\n\r"));

      if(l0.substr(0, 3) == "///")
      {
        if(l1.length() > 0)
          m_content.push_back(l1);
      }
      else if(l0.substr(0, 3) == "/**")
      {
        if(l1.length() > 0)
          m_content.push_back(l1);        
        inBlock = true;
      }
      else if(inBlock)
      {
        m_content.push_back(l1);
      }
    }
  }
}

bool KLComment::isEmpty() const
{
  return m_content.size() == 0;
}

bool KLComment::hasQualifier(const char * qualifier) const
{
  std::string q;
  if(qualifier)
  {
    q = qualifier;
    boost::to_lower(q);
    boost::trim(q);
  }

  if(q.length() == 0)
    return true;

  for(uint32_t i=0;i<m_content.size();i++)
  {
    std::string l = m_content[i];
    boost::trim(l);
    if(l.substr(0, q.length()+1) == "\\"+q)
      return true;
  }
  return false;
}

std::string KLComment::getQualifier(const char * qualifier, const char * defaultResult) const
{
  std::string q;
  if(qualifier)
  {
    q = qualifier;
    boost::to_lower(q);
    boost::trim(q);
  }

  std::map<std::string, std::string>::iterator it = m_qualifiers.find(q);
  if(it != m_qualifiers.end())
    return it->second;

  std::vector<std::string> content;
  std::string insideQualifier;

  for(uint32_t i=0;i<m_content.size();i++)
  {
    std::string l = m_content[i];
    boost::trim(l);

    if(l.substr(0, q.length()+1) == "\\"+q && q != "")
    {
      std::string l2 = l.substr(q.length()+1, 10000);
      boost::trim(l2);
      content.push_back(l2);
    }

    if(l.substr(0, 1) == "\\" && boost::count(l, ' ') == 0)
    {
      if(insideQualifier.length() > 0)
      {
        if(l == "\\end"+insideQualifier)
          insideQualifier = "";
      }
      else
      {
        insideQualifier = l.substr(1, 10000);
      }
    }

    if((q == "" || q == "plaintext") && l.substr(0, 1) != "\\" && insideQualifier.length() == 0)
    {
      content.push_back(l);
    }
  }

  if(content.size() == 0 && defaultResult)
    content.push_back(defaultResult);

  std::string result;
  for(uint32_t i=0;i<content.size();i++)
  {
    if(i>0)
      result += "\n";
    result += content[i];
  }

  m_qualifiers.insert(std::pair<std::string, std::string>(q, result));

  return result;
}

std::string KLComment::getSingleQualifier(const char * qualifier, const char * defaultResult) const
{
  std::string q = getQualifier(qualifier, defaultResult);
  if(q.length() == 0)
    return q;

  std::vector<std::string> lines;
  boost::split(lines, q, boost::is_any_of("\n"));

  return lines[0];
}

std::string KLComment::getQualifierBracket(const char * qualifier, const char * defaultResult) const
{
  if(!qualifier)
    return "";
  std::string q1 = qualifier;
  boost::to_lower(q1);
  boost::trim(q1);

  if(q1.length() == 0)
    return "";

  std::map<std::string, std::string>::iterator it = m_qualifiers.find(q1);
  if(it != m_qualifiers.end())
    return it->second;

  std::string q2 = "end" + q1;

  std::vector<std::string> content;
  bool inBlock = false;
  uint32_t blockIndentation = UINT_MAX;

  for(uint32_t i=0;i<m_content.size();i++)
  {
    std::string l = m_content[i];
    boost::trim_left_if(l, boost::is_any_of(" \t"));

    if(inBlock)
    {
      if(l.substr(0, q2.length() + 1) == "\\" + q2)
      {
        inBlock = false;
      }
      else
      {
        if(q1 == "rst")
        {
          content.push_back(m_content[i]);
        }
        else
        {
          if(blockIndentation == UINT_MAX)
            blockIndentation = m_content[i].length() - l.length();
          content.push_back(m_content[i].substr(blockIndentation, 10000));
        }
      }
    }
    else
    {
      if(l.substr(0, q1.length() + 1) == "\\" + q1)
      {
        inBlock = true;
        blockIndentation = UINT_MAX;
      }
    }
  }

  if(content.size() == 0 && defaultResult)
    content.push_back(defaultResult);

  std::string result;
  for(uint32_t i=0;i<content.size();i++)
  {
    if(i>0)
      result += "\n";
    result += content[i];
  }

  m_qualifiers.insert(std::pair<std::string, std::string>(q1, result));

  return result;
}

std::string KLComment::removeRstRoles(const char * text)
{
  std::string r = text;
  r.erase(boost::remove_if(r, boost::is_any_of("`")), r.end());
  boost::regex re(":[a-zA-Z0-9\\-_]+:");
  return boost::regex_replace(r, re, "");
}

std::string KLComment::getPlainText() const
{
  return getQualifier(NULL, "");
}

std::string KLComment::getBrief() const
{
  return getSingleQualifier("brief", "");
}

std::string KLComment::getCategory() const
{
  return getSingleQualifier("category", "");
}

std::string KLComment::getRst() const
{
  return getQualifierBracket("rst", "");
}

std::string KLComment::getExample() const
{
  return getQualifierBracket("example", "");
}
