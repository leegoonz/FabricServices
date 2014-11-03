// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLFunction__
#define __ASTWrapper_KLFunction__

#include "KLCommented.h"
#include "KLParameter.h"

#include <string>

namespace FabricServices
{

  namespace ASTWrapper
  {

    class KLFunction : public KLCommented
    {
    public:

      virtual ~KLFunction();

      virtual void setExtension(const std::string & extension);
      virtual void setKLFile(const std::string & klFile);

      const std::string & getName() const;
      const std::string & getReturnType() const;
      uint32_t getParameterCount() const;
      const KLParameter * getParameter(uint32_t index) const;

      virtual bool isMethod() const;
      virtual std::string getPrefix() const;
      virtual std::string getSuffix() const;
      virtual const char * getKLType() const;
      virtual std::string getKLCode(bool includeReturnType = true, bool includeKeyWord = true, bool includePrefix = true, bool includeName = true) const;
      virtual std::string getLabel() const;

    protected:

      KLFunction(JSONData data);

    private:
      
      std::string m_name;
      std::string m_returnType;
      std::vector<KLParameter*> m_params;
    };

  };

};


#endif // __ASTWrapper_KLFunction__
