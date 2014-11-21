// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

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
      result.push_back(NameSpace(getWrappedCoreHost(), getPath() + "." + name));
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

std::vector<Func> NameSpace::getFuncs(bool recursive)
{
  std::vector<Func> result;

  FabricCore::DFGStringResult jsonStr = getWrappedCoreHost().getPresetDesc(getPath().c_str());
  FabricCore::Variant jsonVar = FabricCore::Variant::CreateFromJSON(jsonStr.getCString());
  const FabricCore::Variant * membersVar = jsonVar.getDictValue("members");
  for(FabricCore::Variant::DictIter memberIter(*membersVar); !memberIter.isDone(); memberIter.next())
  {
    std::string name = memberIter.getKey()->getStringData();
    const FabricCore::Variant * memberVar = memberIter.getValue();
    const FabricCore::Variant * objectTypeVar = memberVar->getDictValue("objectType");
    std::string objectType = objectTypeVar->getStringData();
    if(objectType == "Func")
    {
      result.push_back(Func(getWrappedCoreHost(), getPath() + "." + name));
    }
    else if(objectType == "NameSpace" && recursive)
    {
      NameSpace ns(getWrappedCoreHost(), getPath() + "." + name);
      std::vector<Func> childResult = ns.getFuncs(recursive);
      result.insert(result.end(), childResult.begin(), childResult.end());
    }
  }

  return result;
}

std::vector<Graph> NameSpace::getGraphs(bool recursive)
{
  std::vector<Graph> result;

  FabricCore::DFGStringResult jsonStr = getWrappedCoreHost().getPresetDesc(getPath().c_str());
  FabricCore::Variant jsonVar = FabricCore::Variant::CreateFromJSON(jsonStr.getCString());
  const FabricCore::Variant * membersVar = jsonVar.getDictValue("members");
  for(FabricCore::Variant::DictIter memberIter(*membersVar); !memberIter.isDone(); memberIter.next())
  {
    std::string name = memberIter.getKey()->getStringData();
    const FabricCore::Variant * memberVar = memberIter.getValue();
    const FabricCore::Variant * objectTypeVar = memberVar->getDictValue("objectType");
    std::string objectType = objectTypeVar->getStringData();
    if(objectType == "Graph")
    {
      result.push_back(Graph(getWrappedCoreHost(), getPath() + "." + name));
    }
    else if(objectType == "NameSpace" && recursive)
    {
      NameSpace ns(getWrappedCoreHost(), getPath() + "." + name);
      std::vector<Graph> childResult = ns.getGraphs(recursive);
      result.insert(result.end(), childResult.begin(), childResult.end());
    }
  }

  return result;
}

NameSpace NameSpace::addNameSpace(char const *displayName)
{
  getWrappedCoreHost().addNamespace(getPath().c_str(), displayName);
  return NameSpace(getWrappedCoreHost(), getPath() + "." + displayName);
}
