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

    class Executable;
    typedef FTL::SharedPtr<Executable> ExecutablePtr;

    class Executable : public Element
    {
      friend class Binding;
      friend class Node;
      friend class View;

    public:

      virtual bool isExec() const { return true; }

      static ExecutablePtr Create( FabricCore::DFGBinding binding, FabricCore::DFGExec exec, const char * execPath );
      virtual ~Executable();

      FabricCore::DFGExecType getExecType() const;

      char const *getExecPath() const 
        { return getElementPath(); }

      std::string getDesc();
      
      char const * getTitle();
      void setTitle(const char * title);

      ExecutablePtr getSubExec(const char * subExecPath);

      PortList getPorts();
      PortPtr getPort(char const * name);
      PortPtr getPort(uint32_t index);
      PortPtr addPort(char const *title, FabricCore::DFGPortType portType, char const *dataType = 0);
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
      
      Executable( FabricCore::DFGBinding binding, FabricCore::DFGExec exec, const char * execPath );
    };

  };

};


#endif // __DFGWrapper_Executable__
