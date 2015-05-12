// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "KLVariable.h"

using namespace FabricServices::CodeCompletion;

KLVariable::KLVariable(const std::string & name, const std::string & type)
:DFGWrapper::KLTypeDesc(type)
{
  m_name = name;
}

KLVariable::KLVariable(const std::string & name, const std::string & type, const std::string & arrayModifier)
:DFGWrapper::KLTypeDesc(type, arrayModifier)
{
  m_name = name;
}

KLVariable::~KLVariable()
{
}

const std::string & KLVariable::getName() const
{
  return m_name;
}
