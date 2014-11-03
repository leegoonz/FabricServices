// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLStruct__
#define __ASTWrapper_KLStruct__

#include "KLType.h"

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
      virtual std::vector<const KLType*> getParents() const = 0;

    protected:

      KLStruct(JSONData data);

    private:
      std::string m_parentStructName;
    };

  };

};


#endif // __ASTWrapper_KLStruct__
