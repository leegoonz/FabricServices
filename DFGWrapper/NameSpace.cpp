// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "NameSpace.h"

using namespace FabricServices::DFGWrapper;

NameSpace::NameSpace(FabricCore::DFGHost host, std::string path)
: Object(host, path)
{
  m_parsed = false;
}

NameSpace::NameSpace(const NameSpace & other)
: Object(other)
{
  m_nameSpaces = other.m_nameSpaces;
  m_presets = other.m_presets;
  m_funcs = other.m_funcs;
  m_graphs = other.m_graphs;
  m_presetsRecursive = other.m_presetsRecursive;
  m_funcsRecursive = other.m_funcsRecursive;
  m_graphsRecursive = other.m_graphsRecursive;
  m_parsed = other.m_parsed;
}

NameSpace::~NameSpace()
{
}

std::vector<NameSpace> & NameSpace::getNameSpaces(bool recursive)
{
  parse();

  if(!recursive)
    return m_nameSpaces;

  if(m_nameSpacesRecursive.size() == 0)
  {
    m_nameSpacesRecursive = m_nameSpaces;
    for(size_t i=0;i<m_nameSpaces.size();i++)
    {
      std::vector<NameSpace> childResult = m_nameSpaces[i].getNameSpaces(recursive);
      m_nameSpacesRecursive.insert(m_nameSpacesRecursive.end(), childResult.begin(), childResult.end());
    }
  }

  return m_nameSpacesRecursive;
}

std::vector<Object> & NameSpace::getPresets(bool recursive)
{
  parse();

  if(!recursive)
    return m_presets;

  if(m_presetsRecursive.size() == 0)
  {  
    m_presetsRecursive = m_presets;
    for(size_t i=0;i<m_nameSpaces.size();i++)
    {
      std::vector<Object> childResult = m_nameSpaces[i].getPresets(recursive);
      m_presetsRecursive.insert(m_presetsRecursive.end(), childResult.begin(), childResult.end());
    }
  }

  return m_presetsRecursive;
}

std::vector<Func> & NameSpace::getFuncs(bool recursive)
{
  parse();

  if(!recursive)
    return m_funcs;

  if(m_funcsRecursive.size() == 0)
  {  
    m_funcsRecursive = m_funcs;
    for(size_t i=0;i<m_nameSpaces.size();i++)
    {
      std::vector<Func> childResult = m_nameSpaces[i].getFuncs(recursive);
      m_funcsRecursive.insert(m_funcsRecursive.end(), childResult.begin(), childResult.end());
    }
  }

  return m_funcsRecursive;
}

std::vector<Graph> & NameSpace::getGraphs(bool recursive)
{
  parse();

  if(!recursive)
    return m_graphs;

  if(m_graphsRecursive.size() == 0)
  {  
    m_graphsRecursive = m_graphs;
    for(size_t i=0;i<m_nameSpaces.size();i++)
    {
      std::vector<Graph> childResult = m_nameSpaces[i].getGraphs(recursive);
      m_graphsRecursive.insert(m_graphsRecursive.end(), childResult.begin(), childResult.end());
    }
  }

  return m_graphsRecursive;
}

NameSpace NameSpace::addNameSpace(char const *displayName)
{
  std::string prefix = getPath();
  if(prefix.length() > 0)
    prefix += ".";

  getWrappedCoreHost().addNamespace(getPath().c_str(), displayName);
  return NameSpace(getWrappedCoreHost(), prefix + displayName);
}

void NameSpace::refresh()
{
  m_nameSpaces.clear();
  m_presets.clear();
  m_funcs.clear();
  m_graphs.clear();
  m_presetsRecursive.clear();
  m_funcsRecursive.clear();
  m_graphsRecursive.clear();
  m_parsed = false;
}

void NameSpace::parse()
{
  if(m_parsed)
    return;
  m_parsed = true;

  std::string prefix = getPath();
  if(prefix.length() > 0)
    prefix += ".";

  FabricCore::DFGStringResult jsonStr = getWrappedCoreHost().getPresetDesc(getPath().c_str());
  FabricCore::Variant jsonVar = FabricCore::Variant::CreateFromJSON(jsonStr.getCString());
  const FabricCore::Variant * membersVar = jsonVar.getDictValue("members");
  for(FabricCore::Variant::DictIter memberIter(*membersVar); !memberIter.isDone(); memberIter.next())
  {
    std::string name = memberIter.getKey()->getStringData();
    const FabricCore::Variant * memberVar = memberIter.getValue();
    const FabricCore::Variant * objectTypeVar = memberVar->getDictValue("objectType");
    std::string objectType = objectTypeVar->getStringData();
    if(objectType == "Preset")
    {
      const FabricCore::Variant * execTypeVar = memberVar->getDictValue("execType");
      std::string execType = execTypeVar->getStringData();
      m_presets.push_back(Object(getWrappedCoreHost(), prefix + name));
      if ( execType == "Func" )
        m_funcs.push_back(Func(getWrappedCoreHost(), prefix + name));
      else if ( execType == "Graph" )
        m_graphs.push_back(Graph(getWrappedCoreHost(), prefix + name));
    }
    else if(objectType == "NameSpace")
    {
      m_nameSpaces.push_back(NameSpace(getWrappedCoreHost(), prefix + name));
    }
  }
}
