// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "SyntaxHighlighter.h"

using namespace FabricServices::CodeCompletion;

SyntaxHighlighter::SyntaxHighlighter()
{
  m_enabled = true;
}

SyntaxHighlighter::~SyntaxHighlighter()
{
  for(size_t i=0;i<m_rules.size();i++)
  {
    delete(m_rules[i]);
  }
}

bool SyntaxHighlighter::isEnabled() const
{
  return m_enabled;
}

void SyntaxHighlighter::setEnabled(bool state)
{
  m_enabled = state;
}

HighlightRule * SyntaxHighlighter::addRule(HighlightRuleType type, const std::string & pattern, const std::string & formatPrefix, const std::string & formatSuffix)
{
  HighlightRule * rule = new HighlightRule(type, pattern, formatPrefix, formatSuffix);
  m_rules.push_back(rule);
  m_lastText = "";
  return rule;
}

uint32_t SyntaxHighlighter::getRuleCount() const
{
  return m_rules.size();
}

const HighlightRule * SyntaxHighlighter::getRule(uint32_t index) const
{
  return m_rules[index];
}

const char * SyntaxHighlighter::getRuleTypeName(HighlightRuleType type) const
{
  switch(type)
  {
    case HighlightRuleType_Keyword:
      return "Keyword";
    case HighlightRuleType_Type:
      return "Type";
    case HighlightRuleType_Comment:
      return "Comment";
    case HighlightRuleType_String:
      return "String";
    case HighlightRuleType_Number:
      return "Number";
    case HighlightRuleType_Constant:
      return "Constant";
    case HighlightRuleType_Function:
      return "Function";
    case HighlightRuleType_Method:
      return "Method";
    case HighlightRuleType_Error:
      return "Error";
    case HighlightRuleType_Highlight:
      return "Highlight";
    case HighlightRuleType_NumItems:
      return "";
  }
  return "";
}

const std::vector<SyntaxHighlighter::Format> & SyntaxHighlighter::getHighlightFormats(const std::string & text) const
{
  if(!m_enabled)
  {
    m_lastFormats.clear();
    m_lastText = "";
    return m_lastFormats;
  }

  if(m_lastText == text)
    return m_lastFormats;

  std::vector<Format> formats;
  uint32_t pos = 0;
  
  for(size_t i=0;i<m_rules.size();i++)
  {
    Format f;
    f.type = m_rules[i]->getRuleType();
    f.prefix = m_rules[i]->getFormatPrefix().c_str();
    f.suffix = m_rules[i]->getFormatSuffix().c_str();

    uint32_t index = m_rules[i]->getIndexIn(text);
    while(index != UINT_MAX)
    {
      f.start = index;
      f.length = m_rules[i]->getMatchedLength();

      if(f.length == 0)
      {
        index = m_rules[i]->getIndexIn(text, index + 1);
      }
      else
      {
        formats.push_back(f);
        index = m_rules[i]->getIndexIn(text, index + f.length);
      }
    }      
  }

  std::map<uint32_t, size_t> sortedIndices;
  for(size_t i=0;i<formats.size();i++)
  {
    std::map<uint32_t, size_t>::iterator it = sortedIndices.find(formats[i].start);
    if(it == sortedIndices.end())
      sortedIndices.insert(std::pair<uint32_t, size_t>(formats[i].start, i));
  }

  m_lastText = text;
  m_lastFormats.clear();
  uint32_t end = 0;
  for(std::map<uint32_t, size_t>::iterator it = sortedIndices.begin(); it != sortedIndices.end(); it++)
  {
    // ensure to avoid overlapping formats
    Format f = formats[it->second];
    if(f.start < end)
      continue;
    m_lastFormats.push_back(f);
    end = f.start + f.length - 1;
  }

  m_lastFormats.insert(m_lastFormats.end(), m_errorFormats.begin(), m_errorFormats.end());
  m_lastFormats.insert(m_lastFormats.end(), m_highlightFormats.begin(), m_highlightFormats.end());

  return m_lastFormats;
}

std::string SyntaxHighlighter::getHighlightedText(const std::string & text) const
{
  const std::vector<Format> & formats = getHighlightFormats(text);
  if(formats.size() == 0)
    return text;

  std::string result;
  uint32_t end = 0;
  for(size_t i=0;i<formats.size();i++)
  {
    if(formats[i].start > end)
      result += text.substr(end, formats[i].start - end);
    result += formats[i].prefix;
    result += text.substr(formats[i].start, formats[i].length);
    result += formats[i].suffix;
    end = formats[i].start + formats[i].length;
  }

  if(end < text.length())
    result += text.substr(end, text.length() - end);

  return result;
}

void SyntaxHighlighter::reportError(uint32_t start, uint32_t length, const char * prefix, const char * suffix)
{
  Format f;
  f.type = HighlightRuleType_Error;
  f.start = start;
  f.length = length;
  f.prefix = prefix;
  f.suffix = suffix;
  m_errorFormats.push_back(f);
  m_lastText = "";
}

void SyntaxHighlighter::clearErrors()
{
  m_errorFormats.clear();
  m_lastText = "";
}

void SyntaxHighlighter::highlight(uint32_t start, uint32_t length, const char * prefix, const char * suffix)
{
  Format f;
  f.type = HighlightRuleType_Highlight;
  f.start = start;
  f.length = length;
  f.prefix = prefix;
  f.suffix = suffix;
  m_highlightFormats.push_back(f);
  m_lastText = "";
}

void SyntaxHighlighter::clearHighlighting()
{
  m_highlightFormats.clear();
  m_lastText = "";
}
