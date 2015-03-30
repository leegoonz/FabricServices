// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __DFGWrapper_Binding__
#define __DFGWrapper_Binding__

#include <FabricCore.h>
#include <string>
#include "Executable.h"

namespace FabricServices
{

  namespace DFGWrapper
  {

    class Binding
    {
      friend class Host;

    public:

      Binding();
      Binding(FabricCore::DFGBinding binding);
      Binding(const Binding & other);
      virtual ~Binding();

      bool isValid() const;
      FabricCore::DFGBinding getWrappedCoreBinding() const;

      FabricCore::RTVal getArgValue(char const *name);
      void setArgValue(char const *name, FabricCore::RTVal value);

      ExecutablePtr getExec();

      void execute();

      void setNotificationCallback(FabricCore::DFGNotificationCallback callback, void * userData);

      // todo
      // bool canConnect(
      //   char const *graphPath,
      //   char const *srcPath,
      //   char const *dstPath,
      //   std::string &failureReason
      //   );

    private:
      FabricCore::DFGBinding m_binding;      
    };

  };

};


#endif // __DFGWrapper_Binding__
