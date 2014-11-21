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

    public:

      Node(const Node & other);
      virtual ~Node();

      FabricCore::DFGBinding getWrappedCoreBinding() const;

      std::string getDesc();
      std::string getObjectType();
      std::string getPath();
      std::string getTitle();
      void setTitle(char const *title);

      // todo: is this the same as getDesc
      std::string exportJSON();

      std::string getMetadata(char const * key);
      void setMetadata(char const * key, char const * metadata, bool canUndo);
      std::string getInstanceMetadata(char const * key);
      void setInstanceMetadata(char const * key, char const * metadata, bool canUndo);

      std::string getImportPathName();
      
      Port addPort(char const *title, FabricCore::DFGPortType portType, char const *dataType = 0);
      // void setPortDefaultValue(char const *path, RTVal defaultValue);

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
