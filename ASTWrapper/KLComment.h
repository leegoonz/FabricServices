// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLComment__
#define __ASTWrapper_KLComment__

#include "KLDecl.h"

#include <string>
#include <map>
#include <vector>

namespace FabricServices
{

  namespace ASTWrapper
  {

    class KLComment : public KLDecl
    {
      friend class KLCommented;
      
    public:
      
      virtual ~KLComment();

      virtual bool isInternal() const;
      bool isEmpty() const;
      bool hasQualifier(const char * qualifier) const;
      std::string getQualifier(const char * qualifier = 0, const char * defaultResult = 0) const;
      std::string getSingleQualifier(const char * qualifier, const char * defaultResult = 0) const;
      std::string getQualifierBracket(const char * qualifier, const char * defaultResult = 0) const;

      std::string getPlainText() const;
      std::string getBrief() const;
      std::string getCategory() const;
      std::string getRst() const;
      std::string getExample() const;

    protected:

      KLComment(JSONData data);

    private:

      void gatherDoxygenContent() const;

      mutable std::vector<std::string> m_content;
      mutable std::map<std::string, std::string> m_qualifiers;
    };

  };

};


#endif // __ASTWrapper_KLComment__
