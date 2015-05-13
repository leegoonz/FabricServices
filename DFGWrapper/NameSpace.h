// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __DFGWrapper_NameSpace__
#define __DFGWrapper_NameSpace__

#include <FabricCore.h>
#include <string>
#include <vector>

#include "Object.h"
#include "Func.h"
#include "Graph.h"

namespace FabricServices
{

  namespace DFGWrapper
  {

    class NameSpace : public Object
    {
      friend class Host;

    public:

      NameSpace(const NameSpace & other);
      virtual ~NameSpace();

      std::vector<NameSpace> & getNameSpaces(bool recursive = false);
      std::vector<Object> & getPresets(bool recursive = false);
      std::vector<Func> & getFuncs(bool recursive = false);
      std::vector<Graph> & getGraphs(bool recursive = false);

      NameSpace addNameSpace(char const *displayName);

      void refresh();

    protected:
      
      NameSpace(FabricCore::DFGHost host, std::string path);
      void parse();

    private: 
      
      std::vector<NameSpace> m_nameSpaces;
      std::vector<Object> m_presets;
      std::vector<Func> m_funcs;
      std::vector<Graph> m_graphs;
      std::vector<NameSpace> m_nameSpacesRecursive;
      std::vector<Object> m_presetsRecursive;
      std::vector<Func> m_funcsRecursive;
      std::vector<Graph> m_graphsRecursive;
      bool m_parsed;
    };

  };

};


#endif // __DFGWrapper_NameSpace__
