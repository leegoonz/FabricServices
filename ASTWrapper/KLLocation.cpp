// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLLocation.h"

using namespace FabricServices::ASTWrapper;

KLLocation::KLLocation(JSONData data)
{
  m_line = data->getDictValue("line")->getSInt32();
  m_column = data->getDictValue("column")->getSInt32();
}

KLLocation::~KLLocation()
{
}

uint32_t KLLocation::getLine() const
{
  return m_line;
}

uint32_t KLLocation::getColumn() const
{
  return m_column;
}

