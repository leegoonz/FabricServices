// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __DFGWrapper_Connection__
#define __DFGWrapper_Connection__

#include <FabricCore.h>
#include <string>
#include "Port.h"

namespace FabricServices
{

  namespace DFGWrapper
  {

    class Connection
    {
      friend class GraphExecutable;

    public:

      Connection(const Connection & other);
      virtual ~Connection();

      bool isValid() const;

      Port getSrc() const;
      Port getDst() const;

    protected:
      
      Connection(Port src, Port dst);

    private:

      Port m_src;
      Port m_dst;
    };

  };

};


#endif // __DFGWrapper_Connection__
