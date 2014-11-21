// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __DFGWrapper_GraphExecutable__
#define __DFGWrapper_GraphExecutable__

#include <FabricCore.h>
#include "Executable.h"

namespace FabricServices
{

  namespace DFGWrapper
  {

    class GraphExecutable : public Executable
    {
      friend class Binding;
      friend class Node;

    public:

      GraphExecutable(const Executable & other);
      GraphExecutable(const GraphExecutable & other);
      virtual ~GraphExecutable();

      // Executable addExecutableFromPreset(char const *parentGraphPath, char const *execPath);
      // GraphExecutable addExecutableWithNewGraph(char const *title = 0);
      // FuncExecutable addExecutableWithNewFunc(char const *title = 0);
      // DFGStringResult addExecutableFromJSON(char const *parentGraphPath, char const *json);

    protected:
      
      GraphExecutable(FabricCore::DFGBinding binding, std::string path);

    };

  };

};


#endif // __DFGWrapper_GraphExecutable__
