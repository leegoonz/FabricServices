// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "NameSpace.h"

using namespace FabricServices::DFGWrapper;

NameSpace::NameSpace(FabricCore::DFGHost host, std::string path)
: Object(host, path)
{
}

NameSpace::NameSpace(const NameSpace & other)
: Object(other)
{
}

NameSpace::~NameSpace()
{
}

std::vector<NameSpace> NameSpace::getNameSpaces(bool recursive)
{
  std::vector<NameSpace> result;

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
    if(objectType == "NameSpace")
    {
      result.push_back(NameSpace(getWrappedCoreHost(), prefix + name));
    }
  }

  if(recursive)
  {
    size_t count = result.size();
    for(size_t i=0;i<count;i++)
    {
      std::vector<NameSpace> childResult = result[i].getNameSpaces(recursive);
      result.insert(result.end(), childResult.begin(), childResult.end());
    }
  }

  return result;
}

std::vector<Object> NameSpace::getPresets(bool recursive)
{
  std::vector<Object> result;

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
      result.push_back(Object(getWrappedCoreHost(), prefix + name));
    }
    else if(objectType == "NameSpace" && recursive)
    {
      NameSpace ns(getWrappedCoreHost(), prefix + name);
      std::vector<Object> childResult = ns.getPresets(recursive);
      result.insert(result.end(), childResult.begin(), childResult.end());
    }
  }

  return result;
}

std::vector<Func> NameSpace::getFuncs(bool recursive)
{
  std::vector<Func> result;

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
      if ( execType == "Func" )
        result.push_back(Func(getWrappedCoreHost(), prefix + name));
    }
    else if(objectType == "NameSpace" && recursive)
    {
      NameSpace ns(getWrappedCoreHost(), prefix + name);
      std::vector<Func> childResult = ns.getFuncs(recursive);
      result.insert(result.end(), childResult.begin(), childResult.end());
    }
  }

  return result;
}

std::vector<Graph> NameSpace::getGraphs(bool recursive)
{
  std::vector<Graph> result;

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
      if ( execType == "Graph" )
        result.push_back(Graph(getWrappedCoreHost(), prefix + name));
    }
    else if(objectType == "NameSpace" && recursive)
    {
      NameSpace ns(getWrappedCoreHost(), prefix + name);
      std::vector<Graph> childResult = ns.getGraphs(recursive);
      result.insert(result.end(), childResult.begin(), childResult.end());
    }
  }

  return result;
}

NameSpace NameSpace::addNameSpace(char const *displayName)
{
  std::string prefix = getPath();
  if(prefix.length() > 0)
    prefix += ".";

  getWrappedCoreHost().addNamespace(getPath().c_str(), displayName);
  return NameSpace(getWrappedCoreHost(), prefix + displayName);
}
