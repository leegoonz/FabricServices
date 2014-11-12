// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLCodeCompletor.h"

using namespace FabricServices;
using namespace FabricServices::CodeCompletion;

KLCodeCompletor::KLCodeCompletor(const FabricCore::Client * client)
{
  m_manager = new ASTWrapper::KLASTManager(client);
  m_owningManager = true;
}

KLCodeCompletor::KLCodeCompletor(ASTWrapper::KLASTManager * manager)
{
  m_manager = manager;
  m_owningManager = false;
}

KLCodeCompletor::~KLCodeCompletor()
{
  if(m_owningManager && m_manager)
    delete(m_manager);
}
