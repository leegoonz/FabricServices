// Copyright 2010-2013 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLDecl__
#define __ASTWrapper_KLDecl__

#include <FabricCore.h>

#include <string>

namespace FabricCore
{

  namespace ASTWrapper
  {

    class KLDecl
    {
    public:

      KLDecl(const FabricCore::Variant & data);

      virtual bool isInternal() const = 0;
      virtual unsigned int getID() const;
      virtual FabricCore::Variant getJSON() const;
      virtual const std::string & getExtension() const;
      virtual const std::string & getKLFile() const;

    private:

      virtual void setExtension(const std::string & extension);
      virtual void setKLFile(const std::string & klFile);

      const FabricCore::Variant * getDictValue(const char * key);
      const char * getStringDictValue(const char * key);

      unsigned int m_id;
      FabricCore::Variant m_data;
      std::string m_extension;
      std::string m_klFile;
    };

  };

};


#endif // __ASTWrapper_KLDecl__
