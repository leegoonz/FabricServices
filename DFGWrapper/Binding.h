// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __DFGWrapper_Binding__
#define __DFGWrapper_Binding__

#include <FabricCore.h>

#include "Node.h"

namespace FabricServices
{

  namespace DFGWrapper
  {

    class Binding : public Node
    {
      friend class Host;

    public:

      Binding(const Binding & other);
      virtual ~Binding();

      FabricCore::RTVal getArgValue(char const *name);
      void setArgValue(char const *name, FabricCore::RTVal value);

      void execute();

    protected:
      
      Binding(FabricCore::DFGBinding binding);

    };

  };

};


#endif // __DFGWrapper_Binding__
