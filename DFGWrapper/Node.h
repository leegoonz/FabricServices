// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __DFGWrapper_Node__
#define __DFGWrapper_Node__

#include <FabricCore.h>
#include <string>
#include <vector>
#include "Executable.h"
#include "Pin.h"

namespace FabricServices
{

  namespace DFGWrapper
  {

    class Node
    {
      friend class Binding;
      friend class GraphExecutable;
      friend class View;

    public:

      Node();
      Node(const Node & other);
      virtual ~Node();

      FabricCore::DFGBinding getWrappedCoreBinding() const;
      char const *getGraphPath() const
        { return m_graphPath.c_str(); }
      char const *getNodePath() const
        { return m_nodePath.c_str(); }

      bool isValid();

      Executable getExecutable();

      std::string getDesc();
      std::string getPath();
      std::string getTitle();
      void setTitle(char const *title);
      std::vector<std::string> getDataTypes();

      FEC_DFGCacheRule getCacheRule() const;
      void setCacheRule(FEC_DFGCacheRule rule);

      std::string getMetadata(char const * key);
      void setMetadata(char const * key, char const * metadata, bool canUndo);

      std::vector<Pin> getPins();
      Pin getPin(char const * name);
      Pin getPin(uint32_t index);

    protected:
      
      Node(
        FabricCore::DFGBinding binding,
        char const *graphPath,
        char const *nodePath
        );

    private:

      FabricCore::DFGBinding m_binding;
      std::string m_graphPath;
      std::string m_nodePath;
      std::string m_objectType;
    };

  };

};


#endif // __DFGWrapper_Node__
