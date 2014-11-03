// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLType__
#define __ASTWrapper_KLType__

#include "KLCommented.h"
#include "KLMethod.h"

#include <string>
#include <map>

namespace FabricServices
{

  namespace ASTWrapper
  {

    class KLType : public KLCommented
    {
      friend class KLFile;

    public:

      virtual ~KLType();
      virtual void setExtension(const std::string & extension);
      virtual void setKLFile(const std::string & klFile);

      const std::string & getName() const;
      virtual const char * getKLType() const = 0;
      virtual std::vector<const KLType*> getParents() const = 0;

      uint32_t getMethodCount() const;
      const KLMethod * getMethod(uint32_t index) const;
      const KLMethod * getMethod(const char * labelOrName) const;
      std::vector<const KLMethod*> getMethods(bool includeInherited = false, bool includeInternal = true, const char * category = 0) const;

      static const KLType * getKLTypeByName(const char * name);

    protected:

      KLType(JSONData data);
      void pushMethod(KLMethod * method);
      std::vector<KLMethod*> m_methods;
      std::map<std::string, uint32_t> m_methodLabelToId;

    private:
      
      std::string m_name;
    };

  };

};


#endif // __ASTWrapper_KLType__
