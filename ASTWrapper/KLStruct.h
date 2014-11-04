// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLStruct__
#define __ASTWrapper_KLStruct__

#include "KLType.h"
#include "KLMember.h"

#include <string>

namespace FabricServices
{

  namespace ASTWrapper
  {

    class KLStruct : public KLType
    {
      friend class KLFile;

    public:

      virtual ~KLStruct();

      virtual const char * getKLType() const;
      virtual std::vector<const KLType*> getParents() const;

      virtual uint32_t getMemberCount(bool includeInherited = true) const;
      virtual const KLMember * getMember(uint32_t index, bool includeInherited = true) const;

    protected:

      KLStruct(const KLFile* klFile, JSONData data);

    private:
      std::string m_parentStructName;
      std::vector<const KLMember*> m_members;
    };

  };

};


#endif // __ASTWrapper_KLStruct__
