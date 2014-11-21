// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __DFGWrapper_Node__
#define __DFGWrapper_Node__

#include <FabricCore.h>
#include <string>
#include "Port.h"

namespace FabricServices
{

  namespace DFGWrapper
  {

    class Node
    {
      friend class Binding;
      friend class GraphExecutable;

    public:

      Node(const Node & other);
      virtual ~Node();

      FabricCore::DFGBinding getWrappedCoreBinding() const;

      Executable getExecutable();

      std::string getDesc();
      std::string getObjectType();
      std::string getPath();
      std::string getTitle();
      void setTitle(char const *title);

      std::string getMetadata(char const * key);
      void setMetadata(char const * key, char const * metadata, bool canUndo);

    protected:
      
      Node(FabricCore::DFGBinding binding, std::string path);

    private:

      FabricCore::DFGBinding m_binding;
      std::string m_path;
      std::string m_objectType;
    };

  };

};


#endif // __DFGWrapper_Node__
