// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "SyntaxHighlighter.h"

using namespace FabricServices::CodeCompletion;

SyntaxHighlighter::SyntaxHighlighter()
{
}

SyntaxHighlighter::~SyntaxHighlighter()
{
  for(size_t i=0;i<m_rules.size();i++)
  {
    delete(m_rules[i]);
  }
}

HighlightRule * SyntaxHighlighter::addRule(HighlightRuleType type, const std::string & pattern, const std::string & formatPrefix, const std::string & formatSuffix)
{
  HighlightRule * rule = new HighlightRule(type, pattern, formatPrefix, formatSuffix);
  m_rules.push_back(rule);
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
    case HighlightRuleType_Method:
      return "Method";
    case HighlightRuleType_NumItems:
      return "";
  }
  return "";
}

std::vector<SyntaxHighlighter::Format> SyntaxHighlighter::getHighlightFormats(const std::string & text) const
{
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

  std::vector<Format> result;
  uint32_t end = 0;
  for(std::map<uint32_t, size_t>::iterator it = sortedIndices.begin(); it != sortedIndices.end(); it++)
  {
    // ensure to avoid overlapping formats
    Format f = formats[it->second];
    if(f.start < end)
      continue;
    result.push_back(f);
    end = f.start + f.length - 1;
  }

  return result;
}

std::string SyntaxHighlighter::getHighlightedText(const std::string & text) const
{
  std::vector<Format> formats = getHighlightFormats(text);
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
