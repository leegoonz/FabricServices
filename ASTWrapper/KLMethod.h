// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLMethod__
#define __ASTWrapper_KLMethod__

#include "KLFunction.h"

#include <string>

namespace FabricServices
{

  namespace ASTWrapper
  {

    class KLMethod : public KLFunction
    {
      friend class KLType;
      friend class KLInterface;
      
    public:

      virtual ~KLMethod();

      const std::string & getThisType() const;
      const std::string & getThisUsage() const;

      virtual bool isMethod() const;
      virtual std::string getPrefix() const;
      virtual std::string getSuffix() const;
      virtual const KLComment * getComments() const;

    protected:

      KLMethod(JSONData data, const std::string & thisType = "");

    private:
      
      std::string m_thisType;
      std::string m_thisUsage;
    };

  };

};


#endif // __ASTWrapper_KLMethod__
