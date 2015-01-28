// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

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
