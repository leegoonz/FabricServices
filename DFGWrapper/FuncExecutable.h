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

      virtual bool isFunc() { return true; }

      static FuncExecutablePtr Create(
        FabricCore::DFGBinding const &dfgBinding,
        char const *execPath,
        FabricCore::DFGExec const &dfgExec
        )
      {
        return new FuncExecutable( dfgBinding, execPath, dfgExec );
      }

      virtual ~FuncExecutable()
      {
      }

      char const* getCode()
      {
        return getDFGExec().getCode();
      }

      void setCode(char const *code)
      {
        getDFGExec().setCode(code);
      }

    protected:
      
      FuncExecutable(
        FabricCore::DFGBinding const &dfgBinding,
        char const *execPath,
        FabricCore::DFGExec const &dfgExec
        )
        : Executable( dfgBinding, execPath, dfgExec )
      {
      }

    };

  };

};


#endif // __DFGWrapper_FuncExecutable__
