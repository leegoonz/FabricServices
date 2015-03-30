// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __DFGWrapper_Port__
#define __DFGWrapper_Port__

#include <FabricCore.h>
#include <string>

#include "EndPoint.h"

namespace FabricServices
{

  namespace DFGWrapper
  {

    class Port : public EndPoint
    {
      friend class Executable;
      friend class View;

    public:

      virtual bool isPort() const { return true; }

      Port(const Port & other);
      virtual ~Port();

      char const *getPortPath() const
        { return getEndPointPath(); }

      virtual std::string getDesc();
      virtual char const *getMetadata(char const * key) const;
      virtual void setMetadata(char const * key, char const * value, bool canUndo = false);

      virtual char const *getName() const;
      virtual char const *getDataType() const;
      virtual char const *getResolvedType() const;

      virtual char const *rename(char const * name);

      virtual FabricCore::RTVal getDefaultValue( char const * dataType = NULL ) const;
      virtual void setDefaultValue( FabricCore::RTVal const &value );

    protected:
      
      Port(FabricCore::DFGBinding binding, FabricCore::DFGExec exec, char const * execPath, char const * portPath);

    };

  };

};


#endif // __DFGWrapper_Port__
