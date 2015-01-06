// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __CodeCompletion_SyntaxHighlighter__
#define __CodeCompletion_SyntaxHighlighter__

#include "HighlightRule.h"
#include <vector>

namespace FabricServices
{

  namespace CodeCompletion
  {

    class SyntaxHighlighter
    {

    public:

      struct Format
      {
        HighlightRuleType type;
        uint32_t start;
        uint32_t length;
        const char * prefix;
        const char * suffix;
      };

      SyntaxHighlighter();
      virtual ~SyntaxHighlighter();

      bool isEnabled() const;
      void setEnabled(bool state);

      // rule management
      HighlightRule * addRule(HighlightRuleType type, const std::string & pattern, const std::string & formatPrefix = "", const std::string & formatSuffix = "");
      uint32_t getRuleCount() const;
      const HighlightRule * getRule(uint32_t index) const;
      const char * getRuleTypeName(HighlightRuleType type) const;

      // highlighting
      virtual const std::vector<Format> & getHighlightFormats(const std::string & text) const;
      virtual std::string getHighlightedText(const std::string & text) const;

      // error reporting
      virtual void reportError(uint32_t start, uint32_t length, const char * prefix = NULL, const char * suffix = NULL);
      virtual void clearErrors();

      // highlighting
      virtual void highlight(uint32_t start, uint32_t length, const char * prefix = NULL, const char * suffix = NULL);
      virtual void clearHighlighting();

    private:

      bool m_enabled;
      std::vector<HighlightRule*> m_rules;
      mutable std::string m_lastText;
      mutable std::vector<Format> m_lastFormats;
      mutable std::vector<Format> m_errorFormats;
      mutable std::vector<Format> m_highlightFormats;
    };

  };

};


#endif // __CodeCompletion_SyntaxHighlighter__
