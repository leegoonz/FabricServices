// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "View.h"
#include "GraphExecutable.h"

using namespace FabricServices::DFGWrapper;

View::View(GraphExecutable graph)
: m_graph(graph)
{
  if(m_graph.isValid())
    m_view = m_graph.getWrappedCoreBinding().createView(graph.getPath().c_str(), &callback, this);
}

View::~View()
{
}

bool View::isValid() const
{
  return m_view.isValid();
}

GraphExecutable View::getGraph()
{
  return m_graph;
}

void View::callback(void * userData, char const * jsonCString, uint32_t jsonLength)
{
  View * view = (View *)userData;
  view->onNotification(jsonCString);

  FabricCore::DFGBinding binding = view->m_graph.getWrappedCoreBinding();

  std::string prefix = view->m_graph.getPath();
  if(prefix.length() > 0)
    prefix += ".";

  FabricCore::Variant notificationsVar = FabricCore::Variant::CreateFromJSON(jsonCString, jsonLength);
  for(uint32_t i=0;i<notificationsVar.getArraySize();i++)
  {
    const FabricCore::Variant * notificationVar = notificationsVar.getArrayElement(i);
    const FabricCore::Variant * descVar = notificationVar->getDictValue("desc");
    std::string descStr = descVar->getStringData();

    if(descStr == "nodeInserted")
    {
      const FabricCore::Variant * nodePathVar = notificationVar->getDictValue("nodePath");
      Node node(binding, prefix + nodePathVar->getStringData());
      view->onNodeInserted(node);
    }
    else if(descStr == "nodeRemoved")
    {
      const FabricCore::Variant * nodePathVar = notificationVar->getDictValue("nodePath");
      Node node(binding, prefix + nodePathVar->getStringData());
      view->onNodeRemoved(node);
    }
    else if(descStr == "pinInserted")
    {
      const FabricCore::Variant * pinPathVar = notificationVar->getDictValue("pinPath");
      Pin pin(binding, prefix + pinPathVar->getStringData());
      view->onPinInserted(pin);
    }
    else if(descStr == "pinRemoved")
    {
      const FabricCore::Variant * pinPathVar = notificationVar->getDictValue("pinPath");
      Pin pin(binding, prefix + pinPathVar->getStringData());
      view->onPinRemoved(pin);
    }
    else if(descStr == "portInserted")
    {
      const FabricCore::Variant * portPathVar = notificationVar->getDictValue("portPath");
      Port port(binding, prefix + portPathVar->getStringData());
      view->onPortInserted(port);
    }
    else if(descStr == "portRemoved")
    {
      const FabricCore::Variant * portPathVar = notificationVar->getDictValue("portPath");
      const FabricCore::Variant * portVar = notificationVar->getDictValue("port");
      const FabricCore::Variant * portTypeVar = portVar->getDictValue("portType");
      Port port(binding, prefix + portPathVar->getStringData(), portTypeVar->getStringData());
      view->onPortRemoved(port);
    }
    else if(descStr == "endPointsConnected")
    {
      const FabricCore::Variant * srcEndPointPathVar = notificationVar->getDictValue("srcEndPointPath");
      const FabricCore::Variant * dstEndPointPathVar = notificationVar->getDictValue("dstEndPointPath");
      Port src(binding, prefix + srcEndPointPathVar->getStringData());
      Port dst(binding, prefix + dstEndPointPathVar->getStringData());
      view->onEndPointsConnected(src, dst);
    }
    else if(descStr == "endPointsDisconnected")
    {
      const FabricCore::Variant * srcEndPointPathVar = notificationVar->getDictValue("srcEndPointPath");
      const FabricCore::Variant * dstEndPointPathVar = notificationVar->getDictValue("dstEndPointPath");
      Port src(binding, prefix + srcEndPointPathVar->getStringData());
      Port dst(binding, prefix + dstEndPointPathVar->getStringData());
      view->onEndPointsDisconnected(src, dst);
    }
    else if(descStr == "nodeMetadataChanged")
    {
      const FabricCore::Variant * nodePathVar = notificationVar->getDictValue("nodePath");
      const FabricCore::Variant * keyVar = notificationVar->getDictValue("key");
      const FabricCore::Variant * valueVar = notificationVar->getDictValue("value");
      Node node(binding, prefix + nodePathVar->getStringData());
      view->onNodeMetadataChanged(node, keyVar->getStringData(), valueVar->getStringData());
    }
    else
    {
      printf("View::callback: Unhandled desc '%s'\n", descStr.c_str());
    }
  }
}
