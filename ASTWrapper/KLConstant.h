// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLConstant__
#define __ASTWrapper_KLConstant__

#include "KLCommented.h"

#include <string>
#include <map>
#include <vector>

namespace FabricServices
{

  namespace ASTWrapper
  {

    class KLConstant : public KLCommented
    {
      friend class KLFile;

    public:

      virtual ~KLConstant();

      const std::string & getName() const;
      const std::string & getType() const;

    protected:
      
      KLConstant(const KLFile* klFile, JSONData data);

    private:
      
      std::string m_name;
      std::string m_type;
    };

  };

};


#endif // __ASTWrapper_KLConstant__
