// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __DFGWrapper_Element__
#define __DFGWrapper_Element__

#include <FabricCore.h>
#include <FTL/SharedPtr.h>
#include <string>

// #include "ExecPort.h"

namespace FabricServices
{

  namespace DFGWrapper
  {

    class Element;
    typedef FTL::SharedPtr<Element> ElementPtr;

    class Element : public FTL::Shareable
    {
    public:

      // Element - Type

      virtual bool isPort() const { return false; }
      virtual bool isExecPort() const { return false; }
      virtual bool isNodePort() const { return false; }
      virtual bool isNode() const { return false; }
      virtual bool isExec() const { return false; }
      virtual bool isFunc() const { return false; }
      virtual bool isGraph() const { return false; }

      // Element - Accessors

      FabricCore::DFGBinding const &getWrappedCoreBinding() const
        { return m_binding; }
      FabricCore::DFGExec const &getWrappedCoreExec() const
        { return m_exec; }
      FabricCore::DFGBinding &getWrappedCoreBinding()
        { return m_binding; }
      FabricCore::DFGExec &getWrappedCoreExec()
        { return m_exec; }
      FabricCore::DFGHost getHost() const
        { return m_exec.getHost(); }

      // Element - Validity

      virtual bool isValid() const
        { return m_binding.isValid() && m_exec.isValid(); }

      virtual char const *getElementPath() const
        { return m_elementPath.c_str(); }

      // Element - Desc

      virtual std::string getDesc() = 0;

      // Element - Metadata

      bool hasMetadata(char const * key) const
      {
        char const *value = getMetadata( key );
        return value && *value;
      }

      virtual char const *getMetadata(char const * key) const = 0;

      virtual void setMetadata(char const * key, char const * value, bool canUndo = false) = 0;

      // Element - Options (JSON-encoded metadata)

      bool hasOption(char const * key) const
        { return hasMetadata( key ); }

      FabricCore::Variant getOption(char const * key) const
      {
        char const *value = getMetadata( key );
        if ( value[0] )
          return FabricCore::Variant::CreateFromJSON( value );
        else
          return FabricCore::Variant();
      }

      void setOption(char const * key, const FabricCore::Variant * var)
      {
        if ( var )
          setMetadata( key, var->getJSONEncoding().getStringData() );
      }

    protected:

      Element()
      {
      }
      
      Element(
        FabricCore::DFGBinding const &binding,
        FabricCore::DFGExec const &exec,
        const char * elementPath
        )
        : m_binding( binding )
        , m_exec( exec )
        , m_elementPath( elementPath )
      {
      }

      Element(
        Element const &other
        )
        : m_binding( other.m_binding )
        , m_exec( other.m_exec )
        , m_elementPath( other.m_elementPath )
      {
      }

      FabricCore::DFGBinding m_binding;
      FabricCore::DFGExec m_exec;
      std::string m_elementPath;
      
    };

  };

};


#endif // __DFGWrapper_Element__
