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
      
      virtual bool isInternal() const;
      bool isEmpty();
      bool hasQualifier(const char * qualifier);
      std::string getQualifier(const char * qualifier = 0, const char * defaultResult = 0);
      std::string getSingleQualifier(const char * qualifier, const char * defaultResult = 0);
      std::string getQualifierBracket(const char * qualifier, const char * defaultResult = 0);

    protected:

      KLComment(JSONData data);

    private:

      void gatherDoxygenContent();

      std::vector<std::string> m_content;
      std::map<std::string, std::string> m_qualifiers;
    };

  };

};


#endif // __ASTWrapper_KLComment__
