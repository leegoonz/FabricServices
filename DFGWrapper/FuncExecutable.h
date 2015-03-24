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

      char const *getFuncPath() const
        { return getExecPath(); }

      std::string getCode();
      void setCode(char const *code);

    protected:
      
      FuncExecutable(
        FabricCore::DFGBinding binding,
        char const *funcPath
        );

    };

  };

};


#endif // __DFGWrapper_FuncExecutable__
