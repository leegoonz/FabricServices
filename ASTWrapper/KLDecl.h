// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLDecl__
#define __ASTWrapper_KLDecl__

#include <FabricCore.h>

#include <string>

namespace FabricServices
{

  namespace ASTWrapper
  {

    class KLASTManager;
    class KLExtension;
    class KLFile;

    typedef const FabricCore::Variant * JSONData;

    class KLDecl
    {
    public:

      virtual ~KLDecl();
      virtual bool isInternal() const = 0;
      virtual uint32_t getID() const;
      virtual const KLASTManager* getASTManager() const;
      virtual const KLExtension* getExtension() const;
      virtual const KLFile* getKLFile() const;

    protected:

      KLDecl(const KLFile* klFile, JSONData data);

      uint32_t getArraySize() const;
      const char * getStringArrayElement(uint32_t index) const;
      const char * getStringDictValue(const char * key) const;

      JSONData getArrayElement(uint32_t index) const;
      JSONData getDictValue(const char * key) const;
      JSONData getArrayDictValue(const char * key) const;

    private:

      uint32_t m_id;
      JSONData m_data;
      const KLFile* m_klFile;
    };

  };

};

#endif // __ASTWrapper_KLDecl__
