// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __DFGWrapper_Object__
#define __DFGWrapper_Object__

#include <FabricCore.h>
#include <string>
#include <vector>

namespace FabricServices
{

  namespace DFGWrapper
  {

    class Object
    {
      friend class NameSpace;

    public:

      Object(const Object & other);
      virtual ~Object();

      FabricCore::DFGHost getWrappedCoreHost() const;
      std::string getPath() const;
      std::string getTitle() const;

    protected:
      
      Object(FabricCore::DFGHost host, std::string path);

    private:

      std::string m_path;
      FabricCore::DFGHost m_host;
    };

  };

};


#endif // __DFGWrapper_NameSpace__