// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __CodeCompletion_HighlightRule__
#define __CodeCompletion_HighlightRule__

#include <string>
#include <boost/regex.hpp>

namespace FabricServices
{

  namespace CodeCompletion
  {
    enum HighlightRuleType
    {
      HighlightRuleType_Comment,
      HighlightRuleType_String,
      HighlightRuleType_Number,
      HighlightRuleType_Keyword,
      HighlightRuleType_Type,
      HighlightRuleType_Constant,
      HighlightRuleType_Method,
      HighlightRuleType_Error,
      HighlightRuleType_NumItems
    };

    class HighlightRule
    {
      friend class SyntaxHighlighter;
      
    public:

      virtual ~HighlightRule();

      HighlightRuleType getRuleType() const;
      const std::string & getPattern() const;
      const std::string & getFormatPrefix() const;
      const std::string & getFormatSuffix() const;

      virtual uint32_t getIndexIn(const std::string & text, uint32_t startIndex = 0) const;
      virtual uint32_t getMatchedLength() const;

    protected:

      HighlightRule(HighlightRuleType type, const std::string & pattern, const std::string & formatPrefix, const std::string & formatSuffix);

    private:

      HighlightRuleType m_type;
      std::string m_pattern;
      std::string m_formatPrefix;
      std::string m_formatSuffix;
      boost::regex m_expression;

      mutable uint32_t m_matchedLength;
    };

  };

};


#endif // __CodeCompletion_HighlightRule__
