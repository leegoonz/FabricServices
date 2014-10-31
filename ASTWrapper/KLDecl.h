// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLDecl__
#define __ASTWrapper_KLDecl__

#include <FabricCore.h>

#include <string>

namespace FabricServices
{

  namespace ASTWrapper
  {

    typedef const FabricCore::Variant * JSONData;

    class KLDecl
    {
    public:

      virtual bool isInternal() const = 0;
      virtual unsigned int getID() const;
      virtual JSONData getJSON() const;
      virtual const std::string & getExtension() const;
      virtual const std::string & getKLFile() const;

    protected:

      KLDecl(JSONData data);
      virtual void setExtension(const std::string & extension);
      virtual void setKLFile(const std::string & klFile);

      JSONData getDictValue(const char * key);
      const char * getStringDictValue(const char * key);

      unsigned int m_id;
      JSONData m_data;
      std::string m_extension;
      std::string m_klFile;
    };

  };

};


#endif // __ASTWrapper_KLDecl__
