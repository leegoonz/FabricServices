// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLInterface.h"

using namespace FabricServices::ASTWrapper;

KLInterface::KLInterface(JSONData data)
: KLType(data)
{

  JSONData members = getArrayDictValue("members");
  if(members)
  {
    for(uint32_t i=0;i<members->getArraySize();i++)
    {
      KLMethod * m = new KLMethod(members->getArrayElement(i), getName());
      pushMethod(m);
    }
  }
}

KLInterface::~KLInterface()
{
  // KLMethods are deleted by the KLType destructor
}

const char * KLInterface::getKLType() const
{
  return "interface";
}
