// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "Command.h"

using namespace FabricServices::Commands;

Command::Command()
{

}

Command::~Command()
{

}

void Command::destroy()
{

}

bool Command::redo()
{
  return invoke();
}
