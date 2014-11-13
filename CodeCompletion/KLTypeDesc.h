// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __CodeCompletion_KLTypeDesc__
#define __CodeCompletion_KLTypeDesc__

#include <string>

namespace FabricServices
{

  namespace CodeCompletion
  {
    class KLTypeDesc
    {
      friend class KLCodeAssistant;
      
    public:

      virtual ~KLTypeDesc();

      const std::string & getType() const;
      std::string getBaseType() const;
      const std::string & getArrayModifier() const;
      bool isArray() const;
      bool isDict() const;
      bool isRef() const;

    protected:

      KLTypeDesc(const std::string & type);
      KLTypeDesc(const std::string & type, const std::string & arrayModifier);

    private:

      std::string m_type;
      std::string m_arrayModifier;
    };

  };

};


#endif // __CodeCompletion_KLTypeDesc__
