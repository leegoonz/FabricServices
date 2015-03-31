// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __DFGWrapper_Connection__
#define __DFGWrapper_Connection__

#include <FabricCore.h>
#include <string>
#include <vector>
#include "EndPoint.h"
#include <FTL/SharedPtr.h>

namespace FabricServices
{

  namespace DFGWrapper
  {
    class Connection;
    typedef FTL::SharedPtr<Connection> ConnectionPtr;
    typedef std::vector<ConnectionPtr> ConnectionList;

    class Connection : public FTL::Shareable
    {
      friend class GraphExecutable;

    public:

      Connection(const Connection & other);
      virtual ~Connection();

      bool isValid();

      EndPointPtr getSrc() const;
      EndPointPtr getDst() const;

    protected:
      
      Connection(EndPointPtr src, EndPointPtr dst);

    private:

      EndPointPtr m_src;
      EndPointPtr m_dst;
    };

  };

};


#endif // __DFGWrapper_Connection__
