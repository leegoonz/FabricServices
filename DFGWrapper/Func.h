// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __DFGWrapper_Func__
#define __DFGWrapper_Func__

#include <FabricCore.h>
#include <string>
#include <vector>

#include "Object.h"

namespace FabricServices
{

  namespace DFGWrapper
  {

    class Func : public Object
    {
      friend class NameSpace;

    public:

      Func(const Func & other);
      virtual ~Func();

    protected:
      
      Func(FabricCore::DFGHost host, std::string path);

    };

  };

};


#endif // __DFGWrapper_NameSpace__
