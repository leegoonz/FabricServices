// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLVariable__
#define __ASTWrapper_KLVariable__

#include "KLCommented.h"

#include <string>
#include <vector>

namespace FabricServices
{

  namespace ASTWrapper
  {

    class KLVariable : public KLCommented
    {
      friend class KLFunctionBody;

    public:

      virtual ~KLVariable();

      virtual bool isInternal() const { return false; }

      const std::string & getType() const;
      uint32_t getCount() const;
      const std::string & getName(uint32_t index) const;
      const std::string & getArrayModifier(uint32_t index) const;

    protected:

      KLVariable(const KLFile* klFile, JSONData data);

    private:
      
      std::string m_type;
      std::vector<std::string> m_names;
      std::vector<std::string> m_arrayModifiers;
    };

  };

};


#endif // __ASTWrapper_KLVariable__
