// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "HighlightRule.h"

using namespace FabricServices::CodeCompletion;

HighlightRule::HighlightRule(HighlightRuleType type, const std::string & pattern, const std::string & formatPrefix, const std::string & formatSuffix)
{
  m_type = type;
  m_pattern = pattern;
  m_formatPrefix = formatPrefix;
  m_formatSuffix = formatSuffix;
  m_expression = boost::regex(pattern.c_str());
  m_matchedLength = 0;
}

HighlightRule::~HighlightRule()
{
}

HighlightRuleType HighlightRule::getRuleType() const
{
  return m_type;
}

const std::string & HighlightRule::getPattern() const
{
  return m_pattern;
}

const std::string & HighlightRule::getFormatPrefix() const
{
  return m_formatPrefix;
}

const std::string & HighlightRule::getFormatSuffix() const
{
  return m_formatSuffix;
}

uint32_t HighlightRule::getIndexIn(const std::string & text, uint32_t startIndex) const
{
  if(startIndex >= text.length())
  {
    m_matchedLength = 0;
    return UINT_MAX;
  }
  boost::match_results<std::string::const_iterator> what;
  boost::match_flag_type flags = boost::match_default;
  std::string::const_iterator s = text.begin() + startIndex;
  std::string::const_iterator e = text.end();
  if(boost::regex_search(s,e,what,m_expression,flags))
  {
    m_matchedLength = what.length();
    return what.position() + startIndex;
  }
  m_matchedLength = 0;
  return UINT_MAX;
}

uint32_t HighlightRule::getMatchedLength() const
{
  return m_matchedLength;
}

