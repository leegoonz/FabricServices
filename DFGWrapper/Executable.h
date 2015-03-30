// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __DFGWrapper_Executable__
#define __DFGWrapper_Executable__

#include <FabricCore.h>
#include <string>
#include <vector>

#include "Element.h"
#include "Port.h"

namespace FabricServices
{

  namespace DFGWrapper
  {

    class Executable : public Element
    {
      friend class Node;
      friend class View;

    public:

      virtual bool isExec() const { return true; }

      Executable(const Executable & other);
      virtual ~Executable();

      virtual char const *getExecPath() const 
        { return getElementPath(); }

      virtual std::string getDesc();
      
      virtual std::string getTitle();
      virtual void setTitle(const char * title);

      Executable getSubExec(const char * subExecPath);

      // todo
      // View createView()

      std::vector<Port> getPorts();
      Port getPort(char const * name);
      Port getPort(uint32_t index);
      Port addPort(char const *title, FabricCore::DFGPortType portType, char const *dataType = 0);
      void removePort(Port port);
      void removePort(char const * name);
      void removePort(uint32_t index);

      FEC_DFGCacheRule getCacheRule() const;
      void setCacheRule(FEC_DFGCacheRule rule);

      std::vector<std::string> getErrors();

      std::string exportJSON();

      virtual char const *getMetadata(char const * key) const;
      virtual void setMetadata(char const * key, char const * metadata, bool canUndo);

      void addExtensionDependency(char const * ext);
      void removeExtensionDependency(char const * ext);

      std::string getImportPathname();
      void setImportPathname( char const *importPathname );

      void attachPreset(char const *parentPresetPath, char const *desiredName);

    protected:
      
      Executable();
      Executable( FabricCore::DFGBinding binding, FabricCore::DFGExec exec, const char * execPath );
    };

  };

};


#endif // __DFGWrapper_Executable__
