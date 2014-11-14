// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLError.h"

using namespace FabricServices::ASTWrapper;

KLError::KLError(FabricCore::Exception e)
{
  m_message = e.getDesc_cstr();
}

KLError::~KLError()
{
}
