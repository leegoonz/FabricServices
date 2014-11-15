// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLASTClient.h"
#include "KLASTManager.h"

using namespace FabricServices::ASTWrapper;

KLASTClient::KLASTClient(KLASTManager * manager)
{
  m_manager = NULL;
  setASTManager(manager);
}

KLASTClient::~KLASTClient()
{
  setASTManager(NULL);
}

bool KLASTClient::hasASTManager() const
{
  return m_manager != NULL;
}

const KLASTManager * KLASTClient::getASTManager() const
{
  return m_manager;
}

KLASTManager * KLASTClient::getASTManager()
{
  return m_manager;
}

bool KLASTClient::setASTManager(KLASTManager * manager)
{
  if(manager != m_manager)
  {
    if(m_manager)
      m_manager->unregisterASTClient(this);
    m_manager = manager;
    if(m_manager)
      m_manager->registerASTClient(this);
    return true;
  }
  return false;
}

