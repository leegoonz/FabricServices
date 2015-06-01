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

      virtual bool isPort() { return false; }
      virtual bool isExecPort() { return false; }
      virtual bool isNodePort() { return false; }
      virtual bool isInstPort() { return false; }
      virtual bool isNode() { return false; }
      virtual bool isInst() { return false; }
      virtual bool isExec() { return false; }
      virtual bool isFunc() { return false; }
      virtual bool isGraph() { return false; }

      // Element - Accessors

      FabricCore::DFGHost getDFGHost()
        { return m_dfgExec.getHost(); }

      FabricCore::DFGBinding &getDFGBinding()
        { return m_dfgBinding; }

      FabricCore::DFGExec &getDFGExec()
        { return m_dfgExec; }

      char const *getExecPath()
        { return m_execPath.c_str(); }
      char const *getElementPath()
        { return m_elementPath.c_str(); }

      // Element - Validity

      virtual bool isValid()
        { return m_dfgBinding.isValid() && m_dfgExec.isValid(); }

      // Element - Desc

      virtual std::string getDesc() = 0;

      // Element - Metadata

      bool hasMetadata(char const * key)
      {
        char const *value = getMetadata( key );
        return value && *value;
      }

      virtual char const *getMetadata(char const * key) = 0;

      virtual void setMetadata(
        char const * key,
        char const * value,
        bool canUndo = false
        ) = 0;

      // Element - Options (JSON-encoded metadata)

      bool hasOption(char const * key)
        { return hasMetadata( key ); }

      FabricCore::Variant getOption(char const * key)
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
        FabricCore::DFGBinding const &dfgBinding,
        char const *execPath,
        FabricCore::DFGExec const &dfgExec,
        char const *elementPath
        )
        : m_dfgBinding( dfgBinding )
        , m_execPath( execPath )
        , m_dfgExec( dfgExec )
        , m_elementPath( elementPath )
      {
      }

      Element(
        FabricCore::DFGBinding const &dfgBinding,
        char const *execPath,
        FabricCore::DFGExec const &dfgExec,
        char const *nodeName,
        char const *portName
        )
        : m_dfgBinding( dfgBinding )
        , m_execPath( execPath )
        , m_dfgExec( dfgExec )
      {
        m_elementPath = nodeName;
        m_elementPath += '.';
        m_elementPath += portName;
      }

      void updateElementPath( char const *newElementPath )
      {
        m_elementPath = newElementPath;
      }

      void updateElementPath(
        char const *newNodeName,
        char const *newPortName 
        )
      {
        m_elementPath = newNodeName;
        m_elementPath += '.';
        m_elementPath += newPortName;
      }

    private:

      FabricCore::DFGBinding m_dfgBinding;
      std::string m_execPath;
      FabricCore::DFGExec m_dfgExec;
      std::string m_elementPath;
      
    };

  };

};


#endif // __DFGWrapper_Element__
