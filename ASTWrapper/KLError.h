// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLError__
#define __ASTWrapper_KLError__

#include <string>

namespace FabricServices
{

  namespace ASTWrapper
  {

    class KLError
    {
      friend class KLFile;

    public:

      virtual ~KLError();

      bool isValid() const;

      const char * getFileName() const;
      int getLine() const;
      int getColumn() const;
      const char * getDescription() const;

    protected:
      
      KLError(const char * message);

    private:
      
      std::string m_fileName;
      int m_line;
      int m_column;
      std::string m_description;
      bool m_valid;
    };

  };

};


#endif // __ASTWrapper_KLError__
