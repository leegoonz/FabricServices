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

    class GraphExecutable;
    typedef FTL::SharedPtr<GraphExecutable> GraphExecutablePtr;

    class Node;
    typedef FTL::SharedPtr<Node> NodePtr;

    class Node : public Element
    {
      friend class Binding;
      friend class GraphExecutable;
      friend class View;

    public:

      virtual bool isNode() const { return true; }

      static NodePtr Create(
        FabricCore::DFGBinding binding,
        FabricCore::DFGExec parentExec,
        char const *execPath,
        char const *nodePath
        );
      virtual ~Node();

      char const *getNodePath() const
        { return getElementPath(); }

      GraphExecutablePtr getOwningGraphExecutable();
      ExecutablePtr getExecutable();

      virtual std::string getDesc();
      char const* getTitle();
      void setTitle(char const *title);

      FEC_DFGCacheRule getCacheRule() const;
      void setCacheRule(FEC_DFGCacheRule rule);

      virtual char const *getMetadata(char const * key) const;
      virtual void setMetadata(char const * key, char const * metadata, bool canUndo);

      std::vector<PinPtr> getPins();
      PinPtr getPin(char const * name);
      PinPtr getPin(uint32_t index);

    protected:
      
      Node(
        FabricCore::DFGBinding binding,
        FabricCore::DFGExec parentExec,
        char const *execPath,
        char const *nodePath
        );

    private:
      std::string m_execPath;
    };

  };

};


#endif // __DFGWrapper_Node__
