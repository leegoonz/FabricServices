// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __DFGWrapper_FuncExecutable__
#define __DFGWrapper_FuncExecutable__

#include <FabricCore.h>
#include "Executable.h"

namespace FabricServices
{

  namespace DFGWrapper
  {

    class FuncExecutable;
    typedef FTL::SharedPtr<FuncExecutable> FuncExecutablePtr;

    class FuncExecutable : public Executable
    {
      friend class Binding;
      friend class GraphExecutable;
      friend class Node;

    public:

      virtual bool isFunc() const { return true; }

      static FuncExecutablePtr Create(
        FabricCore::DFGBinding binding,
        FabricCore::DFGExec exec,
        const char * funcPath
      );

      virtual ~FuncExecutable();

      char const *getFuncPath() const
        { return getExecPath(); }

      char const* getCode();
      void setCode(char const *code);

    protected:
      
      FuncExecutable(
        FabricCore::DFGBinding binding,
        FabricCore::DFGExec exec,
        const char * funcPath
      );

    };

  };

};


#endif // __DFGWrapper_FuncExecutable__
