// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __DFGWrapper_Element__
#define __DFGWrapper_Element__

#include <FabricCore.h>
#include <FTL/SharedPtr.h>
#include <string>

#include "Port.h"

namespace FabricServices
{

  namespace DFGWrapper
  {

    class Element : public FTL::Shareable
    {
    public:

      // Element - Type

      virtual bool isEndPoint() const { return false; }
      virtual bool isPort() const { return false; }
      virtual bool isPin() const { return false; }
      virtual bool isNode() const { return false; }
      virtual bool isExec() const { return false; }
      virtual bool isFunc() const { return false; }
      virtual bool isGraph() const { return false; }

      // Element - Accessors

      FabricCore::DFGBinding const &getWrappedCoreBinding() const
        { return m_binding; }
      char const *getExecPath() const
        { return m_execPath.c_str(); }

      virtual char const *getDataType() const = 0;

      // Element - Validity

      virtual bool isValid() const = 0;

      // Element - Desc

      virtual std::string getDesc() = 0;

      // Element - Metadata

      bool hasMetadata(char const * key) const
        { return getMetadata(key)[0]; }

      virtual char const *getMetadata(char const * key) const = 0;

      virtual void setMetadata(char const * key, char const * value, bool canUndo) = 0;

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
      
      Element(
        FabricCore::DFGBinding const &binding,
        char const *execPath
        )
        : m_binding( binding )
        , m_execPath( execPath )
      {
      }

    private:
      
      FabricCore::DFGBinding m_binding;
      std::string m_execPath;
    };

  };

};


#endif // __DFGWrapper_Element__
