// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __DFGWrapper_Node__
#define __DFGWrapper_Node__

#include <FabricCore.h>
#include <string>

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

      // // node
      // DFGStringResult getDesc(char const *path);
      // DFGStringResult getInstanceDesc(char const *path);
      // void setTitle(char const *path, char const *title);
      // DFGStringResult exportJSON(char const *execPath);
      // char const *getMetadata(char const *pathCStr, char const *keyCStr);
      // void setMetadata(char const *path, char const *key, char const *metadata, bool canUndo);
      // char const *getInstanceMetadata(char const *pathCStr, char const *keyCStr);
      // void setInstanceMetadata(char const *pathCStr, char const *keyCStr, char const *valueCStr, bool canUndo);
      // char const *getImportPathname(char const *path);
      // DFGStringResult addPort(char const *parentGraphPath,char const *title, FEC_DFGPortType portType, char const *dataType = 0);
      // void setPortDefaultValue(char const *path, RTVal defaultValue);

    protected:
      
      Node(FabricCore::DFGBinding binding, std::string path);

    private:

      FabricCore::DFGBinding m_binding;
      std::string m_path;
    };

  };

};


#endif // __DFGWrapper_Node__
