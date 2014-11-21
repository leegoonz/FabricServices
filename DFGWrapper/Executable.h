// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __DFGWrapper_Executable__
#define __DFGWrapper_Executable__

#include <FabricCore.h>
#include <string>
#include "Port.h"

namespace FabricServices
{

  namespace DFGWrapper
  {

    class Executable
    {
      friend class Node;

    public:

      Executable(const Executable & other);
      virtual ~Executable();

      FabricCore::DFGBinding getWrappedCoreBinding() const;

      std::string getDesc();
      std::string getObjectType();
      std::string getPath();
      std::string getTitle();

      std::string exportJSON();

      std::string getMetadata(char const * key);
      void setMetadata(char const * key, char const * metadata, bool canUndo);

      std::string getImportPathName();
      
      Port addPort(char const *title, FabricCore::DFGPortType portType, char const *dataType = 0);

    protected:
      
      Executable(FabricCore::DFGBinding binding, std::string path);

    private:

      FabricCore::DFGBinding m_binding;
      std::string m_path;
      std::string m_objectType;
    };

  };

};


#endif // __DFGWrapper_Executable__
