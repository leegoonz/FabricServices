// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __ASTWrapper_KLError__
#define __ASTWrapper_KLError__

#include <string>
#include <FabricCore.h>

namespace FabricServices
{

  namespace ASTWrapper
  {

    class KLError
    {
      friend class KLFile;

    public:

      virtual ~KLError();

      // const std::string & getNewUserName() const;
      // const std::string & getOldUserName() const;

    protected:
      
      KLError(FabricCore::Exception e);

    private:
      
      std::string m_message;
    };

  };

};


#endif // __ASTWrapper_KLError__
