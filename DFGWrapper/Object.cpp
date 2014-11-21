// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "Object.h"

using namespace FabricServices::DFGWrapper;

Object::Object(FabricCore::DFGHost host, std::string path)
{
  m_host = host;
  m_path = path;
}

Object::Object(const Object & other)
{
  m_host = other.m_host;
  m_path = other.m_path;
}

Object::~Object()
{
}

FabricCore::DFGHost Object::getWrappedCoreHost() const
{
  return m_host;  
}

std::string Object::getPath() const
{
  return m_path;
}

std::string Object::getTitle() const
{
  if(m_path.length() == 0)
    return "";
  int pos = m_path.rfind('.');
  if(pos == std::string::npos)
    return m_path;
  return m_path.substr(pos+1, m_path.length());
}
