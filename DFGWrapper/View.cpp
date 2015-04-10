// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "View.h"
#include "GraphExecutable.h"

using namespace FabricServices::DFGWrapper;

View::View()
{
}

View::View(GraphExecutablePtr graph)
{
  setGraph(graph);
}

bool View::isValid() const
{
  return m_view.isValid();
}

void View::setGraph(GraphExecutablePtr graph)
{
  if(!graph->isValid())
  {
    m_graph = GraphExecutablePtr();
    m_view = FabricCore::DFGView();
  }
  else
  {
    m_graph = graph;
    m_view = m_graph->getWrappedCoreExec().createView(&callback, this);
  } 
}

GraphExecutablePtr View::getGraph()
{
  return m_graph;
}

void View::callback(void * userData, char const * jsonCString, uint32_t jsonLength)
{
  View * view = (View *)userData;
  view->onNotification(jsonCString);
  ExecutablePtr exec(view->m_graph);

  FabricCore::DFGBinding binding = exec->getWrappedCoreBinding();

  std::string prefix = exec->getExecPath();
  if(prefix.length() > 0)
    prefix += ".";

  FabricCore::Variant notificationVar = FabricCore::Variant::CreateFromJSON(jsonCString, jsonLength);
  const FabricCore::Variant * descVar = notificationVar.getDictValue("desc");
  std::string descStr = descVar->getStringData();

  if(descStr != "nodeMetadataChanged" && descStr != "execMetadataChanged")
    printf("View::callback %s\n", jsonCString);

  if(descStr == "nodeInserted")
  {
    const FabricCore::Variant * nodePathVar = notificationVar.getDictValue("nodePath");
    NodePtr node = Node::Create(binding, exec->getWrappedCoreExec(), exec->getExecPath(), nodePathVar->getStringData());
    view->onNodeInserted(node);
  }
  else if(descStr == "nodeRemoved")
  {
    const FabricCore::Variant * nodePathVar = notificationVar.getDictValue("nodePath");
    NodePtr node = Node::Create(binding, exec->getWrappedCoreExec(), exec->getExecPath(), nodePathVar->getStringData());
    view->onNodeRemoved(node);
  }
  else if(descStr == "pinInserted")
  {
    const FabricCore::Variant * pinPathVar = notificationVar.getDictValue("pinPath");
    PinPtr pin = Pin::Create(binding, exec->getWrappedCoreExec(), exec->getExecPath(), pinPathVar->getStringData());
    view->onPinInserted(pin);
  }
  else if(descStr == "pinRemoved")
  {
    const FabricCore::Variant * pinPathVar = notificationVar.getDictValue("pinPath");
    PinPtr pin = Pin::Create(binding, exec->getWrappedCoreExec(), exec->getExecPath(), pinPathVar->getStringData());
    view->onPinRemoved(pin);
  }
  else if(descStr == "portInserted")
  {
    const FabricCore::Variant * portPathVar = notificationVar.getDictValue("portPath");
    PortPtr port = Port::Create(binding, exec->getWrappedCoreExec(), exec->getExecPath(), portPathVar->getStringData());
    view->onPortInserted(port);
  }
  else if(descStr == "portRemoved")
  {
    const FabricCore::Variant * portPathVar = notificationVar.getDictValue("portPath");
    PortPtr port = Port::Create(binding, exec->getWrappedCoreExec(), exec->getExecPath(), portPathVar->getStringData());
    view->onPortRemoved(port);
  }
  else if(descStr == "endPointsConnected")
  {
    const FabricCore::Variant * srcEndPointPathVar = notificationVar.getDictValue("srcEndPointPath");
    const FabricCore::Variant * dstEndPointPathVar = notificationVar.getDictValue("dstEndPointPath");
    EndPointPtr src = EndPoint::Create(binding, exec->getWrappedCoreExec(), exec->getExecPath(), srcEndPointPathVar->getStringData());
    EndPointPtr dst = EndPoint::Create(binding, exec->getWrappedCoreExec(), exec->getExecPath(), dstEndPointPathVar->getStringData());
    view->onEndPointsConnected(src, dst);
  }
  else if(descStr == "endPointsDisconnected")
  {
    const FabricCore::Variant * srcEndPointPathVar = notificationVar.getDictValue("srcEndPointPath");
    const FabricCore::Variant * dstEndPointPathVar = notificationVar.getDictValue("dstEndPointPath");
    EndPointPtr src = EndPoint::Create(binding, exec->getWrappedCoreExec(), exec->getExecPath(), srcEndPointPathVar->getStringData());
    EndPointPtr dst = EndPoint::Create(binding, exec->getWrappedCoreExec(), exec->getExecPath(), dstEndPointPathVar->getStringData());
    view->onEndPointsDisconnected(src, dst);
  }
  else if(descStr == "nodeMetadataChanged")
  {
    const FabricCore::Variant * nodePathVar = notificationVar.getDictValue("nodePath");
    const FabricCore::Variant * keyVar = notificationVar.getDictValue("key");
    const FabricCore::Variant * valueVar = notificationVar.getDictValue("value");
    NodePtr node = Node::Create(binding, exec->getWrappedCoreExec(), exec->getExecPath(), nodePathVar->getStringData());
    view->onNodeMetadataChanged(node, keyVar->getStringData(), valueVar->getStringData());
  }
  else if(descStr == "nodeTitleChanged")
  {
    const FabricCore::Variant * nodePathVar = notificationVar.getDictValue("nodePath");
    const FabricCore::Variant * titleVar = notificationVar.getDictValue("title");
    NodePtr node = Node::Create(binding, exec->getWrappedCoreExec(), exec->getExecPath(), nodePathVar->getStringData());
    view->onNodeTitleChanged(node, titleVar->getStringData());
  }
  else if(descStr == "portRenamed")
  {
    const FabricCore::Variant * oldPathVar = notificationVar.getDictValue("oldPath");
    const FabricCore::Variant * newPathVar = notificationVar.getDictValue("newPath");
    std::string oldPath = oldPathVar->getStringData();
    std::string newPath = newPathVar->getStringData();
    PortPtr port = Port::Create(binding, exec->getWrappedCoreExec(), exec->getExecPath(), newPath.c_str());
    view->onPortRenamed(port, oldPath.c_str());
  }
  else if(descStr == "pinRenamed")
  {
    const FabricCore::Variant * oldPathVar = notificationVar.getDictValue("oldPath");
    const FabricCore::Variant * newPathVar = notificationVar.getDictValue("newPath");
    std::string oldPath = oldPathVar->getStringData();
    if(oldPath.rfind('.') != std::string::npos)
      oldPath = oldPath.substr(oldPath.find('.')+1, oldPath.length());
    PinPtr pin = Pin::Create(binding, exec->getWrappedCoreExec(), exec->getExecPath(), newPathVar->getStringData());
    view->onPinRenamed(pin, oldPath.c_str());
  }
  else if(descStr == "execMetadataChanged")
  {
    const FabricCore::Variant * keyVar = notificationVar.getDictValue("key");
    const FabricCore::Variant * valueVar = notificationVar.getDictValue("value");
    view->onExecMetadataChanged(exec, keyVar->getStringData(), valueVar->getStringData());
  }
  else if(descStr == "extDepAdded")
  {
    const FabricCore::Variant * nameVar = notificationVar.getDictValue("name");
    const FabricCore::Variant * versionRangeVar = notificationVar.getDictValue("versionRange");
    view->onExtDepAdded(nameVar->getStringData(), versionRangeVar->getStringData());
  }
  else if(descStr == "extDepRemoved")
  {
    const FabricCore::Variant * nameVar = notificationVar.getDictValue("name");
    const FabricCore::Variant * versionRangeVar = notificationVar.getDictValue("versionRange");
    view->onExtDepRemoved(nameVar->getStringData(), versionRangeVar->getStringData());
  }
  else if(descStr == "nodeCacheRuleChanged")
  {
    const FabricCore::Variant * nodePathVar = notificationVar.getDictValue("nodePath");
    const FabricCore::Variant * cacheRuleVar = notificationVar.getDictValue("cacheRule");
    view->onNodeCacheRuleChanged(nodePathVar->getStringData(), cacheRuleVar->getStringData());
  }
  else if(descStr == "execCacheRuleChanged")
  {
    const FabricCore::Variant * execPathVar = notificationVar.getDictValue("execPath");
    const FabricCore::Variant * cacheRuleVar = notificationVar.getDictValue("cacheRule");
    view->onExecCacheRuleChanged(execPathVar->getStringData(), cacheRuleVar->getStringData());
  }
  else if(descStr == "portResolvedTypeChanged")
  {
    const FabricCore::Variant * portPathVar = notificationVar.getDictValue("portPath");
    const FabricCore::Variant * resolvedTypeVar = notificationVar.getDictValue("resolvedType");
    PortPtr port = Port::Create(binding, exec->getWrappedCoreExec(), exec->getExecPath(), portPathVar->getStringData());
    if(resolvedTypeVar->isString())
      view->onPortResolvedTypeChanged(port, resolvedTypeVar->getStringData());
    else
      view->onPortResolvedTypeChanged(port, "");
  }
  else if(descStr == "pinResolvedTypeChanged")
  {
    const FabricCore::Variant * pinPathVar = notificationVar.getDictValue("pinPath");
    const FabricCore::Variant * resolvedTypeVar = notificationVar.getDictValue("resolvedType");
    PinPtr pin = Pin::Create(binding, exec->getWrappedCoreExec(), exec->getExecPath(), pinPathVar->getStringData());
    if(resolvedTypeVar->isString())
      view->onPinResolvedTypeChanged(pin, resolvedTypeVar->getStringData());
    else
      view->onPinResolvedTypeChanged(pin, "");
  }
  else
  {
    printf("View::callback: Unhandled desc '%s', '%s'\n", descStr.c_str(), jsonCString);
  }
}
