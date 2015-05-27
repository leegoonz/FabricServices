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

  if(descStr == "nodeInserted")
  {
    const FabricCore::Variant * nodePathVar = notificationVar.getDictValue("path");
    NodePtr node = Node::Create(binding, exec->getWrappedCoreExec(), exec->getExecPath(), nodePathVar->getStringData());
    view->onNodeInserted(node);
  }
  else if(descStr == "nodeRemoved")
  {
    const FabricCore::Variant * nodePathVar = notificationVar.getDictValue("path");
    NodePtr node = Node::Create(binding, exec->getWrappedCoreExec(), exec->getExecPath(), nodePathVar->getStringData());
    view->onNodeRemoved(node);
  }
  else if(descStr == "nodePortInserted")
  {
    const FabricCore::Variant * nodePortPathVar = notificationVar.getDictValue("path");
    NodePortPtr nodePort = NodePort::Create(binding, exec->getWrappedCoreExec(), exec->getExecPath(), nodePortPathVar->getStringData());
    view->onNodePortInserted(nodePort);
  }
  else if(descStr == "nodePortRemoved")
  {
    const FabricCore::Variant * nodePortPathVar = notificationVar.getDictValue("path");
    NodePortPtr nodePort = NodePort::Create(binding, exec->getWrappedCoreExec(), exec->getExecPath(), nodePortPathVar->getStringData());
    view->onNodePortRemoved(nodePort);
  }
  else if(descStr == "execPortInserted")
  {
    const FabricCore::Variant * portPathVar = notificationVar.getDictValue("path");
    ExecPortPtr port = ExecPort::Create(binding, exec->getWrappedCoreExec(), exec->getExecPath(), portPathVar->getStringData());
    view->onExecPortInserted(port);
  }
  else if(descStr == "execPortRemoved")
  {
    const FabricCore::Variant * portPathVar = notificationVar.getDictValue("path");
    ExecPortPtr port = ExecPort::Create(binding, exec->getWrappedCoreExec(), exec->getExecPath(), portPathVar->getStringData());
    view->onExecPortRemoved(port);
  }
  else if(descStr == "endPointsConnected")
  {
    const FabricCore::Variant * srcPortPathVar = notificationVar.getDictValue("srcPath");
    const FabricCore::Variant * dstPortPathVar = notificationVar.getDictValue("dstPath");
    PortPtr src = Port::Create(binding, exec->getWrappedCoreExec(), exec->getExecPath(), srcPortPathVar->getStringData());
    PortPtr dst = Port::Create(binding, exec->getWrappedCoreExec(), exec->getExecPath(), dstPortPathVar->getStringData());
    view->onPortsConnected(src, dst);
  }
  else if(descStr == "endPointsDisconnected")
  {
    const FabricCore::Variant * srcPortPathVar = notificationVar.getDictValue("srcPath");
    const FabricCore::Variant * dstPortPathVar = notificationVar.getDictValue("dstPath");
    PortPtr src = Port::Create(binding, exec->getWrappedCoreExec(), exec->getExecPath(), srcPortPathVar->getStringData());
    PortPtr dst = Port::Create(binding, exec->getWrappedCoreExec(), exec->getExecPath(), dstPortPathVar->getStringData());
    view->onPortsDisconnected(src, dst);
  }
  else if(descStr == "nodeMetadataChanged")
  {
    const FabricCore::Variant * nodePathVar = notificationVar.getDictValue("path");
    const FabricCore::Variant * keyVar = notificationVar.getDictValue("key");
    const FabricCore::Variant * valueVar = notificationVar.getDictValue("value");
    NodePtr node = Node::Create(binding, exec->getWrappedCoreExec(), exec->getExecPath(), nodePathVar->getStringData());
    view->onNodeMetadataChanged(node, keyVar->getStringData(), valueVar->getStringData());
  }
  else if(descStr == "nodeTitleChanged")
  {
    const FabricCore::Variant * nodePathVar = notificationVar.getDictValue("path");
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
    ExecPortPtr port = ExecPort::Create(binding, exec->getWrappedCoreExec(), exec->getExecPath(), newPath.c_str());
    view->onExecPortRenamed(port, oldPath.c_str());
  }
  else if(descStr == "nodePortRenamed")
  {
    const FabricCore::Variant * oldPathVar = notificationVar.getDictValue("oldPath");
    const FabricCore::Variant * newPathVar = notificationVar.getDictValue("newPath");
    std::string oldPath = oldPathVar->getStringData();
    if(oldPath.rfind('.') != std::string::npos)
      oldPath = oldPath.substr(oldPath.find('.')+1, oldPath.length());
    NodePortPtr nodePort = NodePort::Create(binding, exec->getWrappedCoreExec(), exec->getExecPath(), newPathVar->getStringData());
    view->onNodePortRenamed(nodePort, oldPath.c_str());
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
    const FabricCore::Variant * nodePathVar = notificationVar.getDictValue("path");
    const FabricCore::Variant * cacheRuleVar = notificationVar.getDictValue("cacheRule");
    view->onNodeCacheRuleChanged(nodePathVar->getStringData(), cacheRuleVar->getStringData());
  }
  else if(descStr == "execCacheRuleChanged")
  {
    const FabricCore::Variant * execPathVar = notificationVar.getDictValue("path");
    const FabricCore::Variant * cacheRuleVar = notificationVar.getDictValue("cacheRule");
    view->onExecCacheRuleChanged(execPathVar->getStringData(), cacheRuleVar->getStringData());
  }
  else if(descStr == "portResolvedTypeChanged")
  {
    const FabricCore::Variant * portPathVar = notificationVar.getDictValue("path");
    const FabricCore::Variant * resolvedTypeVar = notificationVar.getDictValue("resolvedType");
    ExecPortPtr port = ExecPort::Create(binding, exec->getWrappedCoreExec(), exec->getExecPath(), portPathVar->getStringData());
    if(resolvedTypeVar->isString())
      view->onExecPortResolvedTypeChanged(port, resolvedTypeVar->getStringData());
    else
      view->onExecPortResolvedTypeChanged(port, "");
  }
  else if(descStr == "portTypeSpecChanged")
  {
    const FabricCore::Variant * portPathVar = notificationVar.getDictValue("path");
    const FabricCore::Variant * typeSpecVar = notificationVar.getDictValue("typeSpec");
    ExecPortPtr port = ExecPort::Create(binding, exec->getWrappedCoreExec(), exec->getExecPath(), portPathVar->getStringData());
    if(typeSpecVar->isString())
      view->onExecPortTypeSpecChanged(port, typeSpecVar->getStringData());
    else
      view->onExecPortTypeSpecChanged(port, "");
  }
  else if(descStr == "nodePortResolvedTypeChanged")
  {
    const FabricCore::Variant * nodePortPathVar = notificationVar.getDictValue("path");
    const FabricCore::Variant * resolvedTypeVar = notificationVar.getDictValue("resolvedType");
    NodePortPtr nodePort = NodePort::Create(binding, exec->getWrappedCoreExec(), exec->getExecPath(), nodePortPathVar->getStringData());
    if(resolvedTypeVar->isString())
      view->onNodePortResolvedTypeChanged(nodePort, resolvedTypeVar->getStringData());
    else
      view->onNodePortResolvedTypeChanged(nodePort, "");
  }
  else if(descStr == "portMetadataChanged")
  {
    const FabricCore::Variant * portPathVar = notificationVar.getDictValue("path");
    const FabricCore::Variant * keyVar = notificationVar.getDictValue("key");
    const FabricCore::Variant * valueVar = notificationVar.getDictValue("value");
    ExecPortPtr port = ExecPort::Create(binding, exec->getWrappedCoreExec(), exec->getExecPath(), portPathVar->getStringData());
    if(valueVar->isString())
      view->onExecPortMetadataChanged(port, keyVar->getStringData(), valueVar->getStringData());
    else
      view->onExecPortMetadataChanged(port, keyVar->getStringData(), "");
  }
  else if(descStr == "nodePortMetadataChanged")
  {
    const FabricCore::Variant * nodePortPathVar = notificationVar.getDictValue("path");
    const FabricCore::Variant * keyVar = notificationVar.getDictValue("key");
    const FabricCore::Variant * valueVar = notificationVar.getDictValue("value");
    NodePortPtr nodePort = NodePort::Create(binding, exec->getWrappedCoreExec(), exec->getExecPath(), nodePortPathVar->getStringData());
    if(valueVar->isString())
      view->onNodePortMetadataChanged(nodePort, keyVar->getStringData(), valueVar->getStringData());
    else
      view->onNodePortMetadataChanged(nodePort, keyVar->getStringData(), "");
  }
  else if(descStr == "nodePortTypeChanged")
  {
    const FabricCore::Variant * nodePortPathVar = notificationVar.getDictValue("path");
    const FabricCore::Variant * newPortTypeVar = notificationVar.getDictValue("newPortType");
    if(newPortTypeVar->isString())
    {
      std::string newPortType = newPortTypeVar->getStringData();
      NodePortPtr nodePort = NodePort::Create(binding, exec->getWrappedCoreExec(), exec->getExecPath(), nodePortPathVar->getStringData());
      if(newPortType == "In")
        view->onNodePortTypeChanged(nodePort, FabricCore::DFGPortType_In);
      else if(newPortType == "Out")
        view->onNodePortTypeChanged(nodePort, FabricCore::DFGPortType_Out);
      else if(newPortType == "IO")
        view->onNodePortTypeChanged(nodePort, FabricCore::DFGPortType_IO);
    }
  }
  else if(descStr == "execPortOutsidePortTypeChanged")
  {
    const FabricCore::Variant * portPathVar = notificationVar.getDictValue("path");
    const FabricCore::Variant * newPortTypeVar = notificationVar.getDictValue("newPortType");
    if(newPortTypeVar->isString())
    {
      std::string newPortType = newPortTypeVar->getStringData();
      ExecPortPtr port = ExecPort::Create(binding, exec->getWrappedCoreExec(), exec->getExecPath(), portPathVar->getStringData());
      if(newPortType == "In")
        view->onExecPortTypeChanged(port, FabricCore::DFGPortType_In);
      else if(newPortType == "Out")
        view->onExecPortTypeChanged(port, FabricCore::DFGPortType_Out);
      else if(newPortType == "IO")
        view->onExecPortTypeChanged(port, FabricCore::DFGPortType_IO);
    }
  }
  else
  {
    printf("View::callback: Unhandled desc '%s', '%s'\n", descStr.c_str(), jsonCString);
  }
}
