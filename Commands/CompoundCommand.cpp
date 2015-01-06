// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "CompoundCommand.h"

#include <stdlib.h>

using namespace FabricServices::Commands;

CompoundCommand::CompoundCommand()
{

}

CompoundCommand::~CompoundCommand()
{
  for(size_t i=0;i<m_commands.size();i++)
    delete(m_commands[i]);
}

const char * CompoundCommand::getName() const
{
  if(m_commands.size() == 0)
    return "";
  return m_commands.back()->getName();
}

const char * CompoundCommand::getShortDesc() const
{
  if(m_commands.size() == 0)
    return "";
  return m_commands.back()->getShortDesc();
}

const char * CompoundCommand::getFullDesc() const
{
  if(m_commands.size() == 0)
    return "";
  return m_commands.back()->getFullDesc();
}

bool CompoundCommand::add(Command * command)
{
  if(!command->invoke())
    return false;
  m_commands.push_back(command);
  return true;
}

bool CompoundCommand::isEmpty() const
{
  return m_commands.size() == 0;
}

bool CompoundCommand::invoke()
{
  // we have already invoked our child commands on addCommand
  return true;
}

bool CompoundCommand::undo()
{
  for(int i=m_commands.size()-1;i>=0;i--)
  {
    if(!m_commands[i]->undo())
      return false;
  }
  return true;
}

bool CompoundCommand::redo()
{
  for(size_t i=0;i<m_commands.size();i++)
  {
    if(!m_commands[i]->redo())
      return false;
  }
  return true;
}

void CompoundCommand::destroy()
{
  for(size_t i=0;i<m_commands.size();i++)
    m_commands[i]->destroy();
} 

