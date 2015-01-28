// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __DFGWrapper_FuncExecutable__
#define __DFGWrapper_FuncExecutable__

#include <FabricCore.h>
#include "Executable.h"

namespace FabricServices
{

  namespace DFGWrapper
  {

    class FuncExecutable : public Executable
    {
      friend class GraphExecutable;
      friend class Node;

    public:

      FuncExecutable(const Executable & other);
      FuncExecutable(const FuncExecutable & other);
      virtual ~FuncExecutable();

      std::string getCode();
      void setCode(char const *code);

    protected:
      
      FuncExecutable(FabricCore::DFGBinding binding, std::string path);

    };

  };

};


#endif // __DFGWrapper_FuncExecutable__
