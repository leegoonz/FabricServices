// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __DFGWrapper_Executable__
#define __DFGWrapper_Executable__

#include <FabricCore.h>
#include <string>
#include <vector>

#include "Element.h"
#include "ExecPort.h"

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

      virtual bool isExec() { return true; }

      static ExecutablePtr Create(
        FabricCore::DFGBinding const &dfgBinding,
        char const *execPath,
        FabricCore::DFGExec const &dfgExec
        );

      virtual ~Executable()
      {
      }

      char const *getExecPath()
        { return getElementPath(); }

      FabricCore::DFGExecType getExecType()
      {
        return getDFGExec().getType();
      }

      virtual std::string getDesc()
      {
        return getDFGExec().getDesc().getCString();
      }
      
      char const * getTitle()
      {
        return getDFGExec().getTitle();
      }

      void setTitle(const char * title)
      {
        getDFGExec().setTitle( title );
      }

      ExecutablePtr getSubExec(const char * subExecPath);

      ExecPortPtr addExecPort(
        char const *title,
        FabricCore::DFGPortType portType,
        char const *dataType = 0
        );

      ExecPortList getExecPorts();
      ExecPortPtr getExecPort(char const * name);
      ExecPortPtr getExecPort(uint32_t index);

      void removeExecPort(char const * name);
      void removeExecPort(uint32_t index);

      FEC_DFGCacheRule getCacheRule()
      {
        return getDFGExec().getCacheRule();
      }

      void setCacheRule(FEC_DFGCacheRule rule)
      {
        getDFGExec().setCacheRule(rule);
      }

      virtual std::vector<std::string> getErrors();

      std::string exportJSON()
      {
        return getDFGExec().exportJSON().getCString();
      }

      virtual char const *getMetadata(char const * key)
      {
        return getDFGExec().getMetadata(key);
      }

      virtual void setMetadata(
        char const * key,
        char const * metadata,
        bool canUndo
        )
      {
        return getDFGExec().setMetadata(key, metadata, canUndo);
      }

      void addExtensionDependency(char const * ext)
      {
        getDFGExec().addExtDep(ext);
      }

      void removeExtensionDependency(char const * ext)
      {
        getDFGExec().removeExtDep(ext);
      }

      uint32_t getNumExtensionDependencies();
      std::string getExtensionDependencyName(uint32_t index);
      std::string getExtensionDependencyVersion(uint32_t index);

      char const *getImportPathname();
      void setImportPathname( char const *importPathname );

      void attachPreset(char const *parentPresetPath, char const *desiredName);

    protected:
      
      Executable(
        FabricCore::DFGBinding const &dfgBinding,
        char const *execPath,
        FabricCore::DFGExec const &dfgExec
        )
        : Element(
          dfgBinding,
          execPath,
          dfgExec,
          ""
          )
      {
      }

    };

  };

};


#endif // __DFGWrapper_Executable__
