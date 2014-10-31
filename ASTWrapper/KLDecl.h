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

      virtual ~KLDecl();
      virtual bool isInternal() const = 0;
      virtual unsigned int getID() const;
      virtual const std::string & getExtension() const;
      virtual const std::string & getKLFile() const;

    protected:

      KLDecl(JSONData data);
      virtual void setExtension(const std::string & extension);
      virtual void setKLFile(const std::string & klFile);

      unsigned int getArraySize() const;
      const char * getStringArrayElement(unsigned int index) const;
      const char * getStringDictValue(const char * key) const;

      JSONData getArrayElement(unsigned int index) const;
      JSONData getDictValue(const char * key) const;
      JSONData getArrayDictValue(const char * key) const;

      static const KLDecl * getKLDeclByID(unsigned int id);

    private:

      unsigned int m_id;
      JSONData m_data;
      std::string m_extension;
      std::string m_klFile;
    };

  };

};


#endif // __ASTWrapper_KLDecl__
