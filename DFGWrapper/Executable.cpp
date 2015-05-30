// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#include "FuncExecutable.h"
#include "GraphExecutable.h"

using namespace FabricServices::DFGWrapper;

ExecutablePtr Executable::Create(
  FabricCore::DFGBinding const &dfgBinding,
  char const *execPath,
  FabricCore::DFGExec const &dfgExec
  )
{
  switch ( dfgExec.getType() )
  {
    case FabricCore::DFGExecType_Func:
      return FuncExecutable::Create( dfgBinding, execPath, dfgExec );
    case FabricCore::DFGExecType_Graph:
      return GraphExecutable::Create( dfgBinding, execPath, dfgExec );
    default:
      return ExecutablePtr();
  }
}

ExecutablePtr Executable::getSubExec(const char * relExecPath)
{
  std::string absExecPath = getExecPath();
  if ( !absExecPath.empty() )
    absExecPath += '.';
  absExecPath += relExecPath;
  return Executable::Create(
    getDFGBinding(),
    absExecPath.c_str(),
    getDFGExec().getSubExec(relExecPath)
    );
}

std::vector<std::string> Executable::getErrors()
{
  std::vector<std::string> result;
  FabricCore::Variant descVar = FabricCore::Variant::CreateFromJSON(getDesc().c_str());
  const FabricCore::Variant * errorsVar = descVar.getDictValue("errors");
  if(!errorsVar)
    return result;
  for(uint32_t i=0;i<errorsVar->getArraySize();i++)
  {
    const FabricCore::Variant * errorVar = errorsVar->getArrayElement(i);
    std::string errorStr = errorVar->getStringData();
    result.push_back(errorStr);
  }
  return result;
}

uint32_t Executable::getNumExtensionDependencies()
{
  FabricCore::Variant descVar = FabricCore::Variant::CreateFromJSON(getDesc().c_str());
  const FabricCore::Variant * extDepsVar = descVar.getDictValue("extDeps");
  if(!extDepsVar)
    return 0;
  if(!extDepsVar->isDict())
    return 0;

  uint32_t result = 0;
  for(FabricCore::Variant::DictIter keyIter(*extDepsVar); !keyIter.isDone(); keyIter.next())
    result++;
  return result;
}

std::string Executable::getExtensionDependencyName(uint32_t index)
{
  FabricCore::Variant descVar = FabricCore::Variant::CreateFromJSON(getDesc().c_str());
  const FabricCore::Variant * extDepsVar = descVar.getDictValue("extDeps");
  if(!extDepsVar)
    return "";
  if(!extDepsVar->isDict())
    return "";

  uint32_t offset = 0;
  for(FabricCore::Variant::DictIter keyIter(*extDepsVar); !keyIter.isDone(); keyIter.next())
  {
    if(offset == index)
      return keyIter.getKey()->getStringData();
    offset++;
  }
  return "";
}

std::string Executable::getExtensionDependencyVersion(uint32_t index)
{
  FabricCore::Variant descVar = FabricCore::Variant::CreateFromJSON(getDesc().c_str());
  const FabricCore::Variant * extDepsVar = descVar.getDictValue("extDeps");
  if(!extDepsVar)
    return "";
  if(!extDepsVar->isDict())
    return "";

  uint32_t offset = 0;
  for(FabricCore::Variant::DictIter keyIter(*extDepsVar); !keyIter.isDone(); keyIter.next())
  {
    if(offset == index)
      return keyIter.getValue()->getStringData();
    offset++;
  }
  return "";
}

char const *Executable::getImportPathname()
{
  return getDFGExec().getImportPathname();
}

void Executable::setImportPathname( char const *importPathname )
{
  getDFGExec().setImportPathname(importPathname);
}

ExecPortList Executable::getExecPorts()
{
  ExecPortList result;
  unsigned execPortCount = getDFGExec().getExecPortCount();
  result.reserve( execPortCount );
  for(unsigned int i=0;i<execPortCount;i++)
    result.push_back( getExecPort(i) );
  return result;
}

ExecPortPtr Executable::getExecPort(char const * path)
{
  return ExecPort::Create(
    getDFGBinding(),
    getExecPath(),
    getDFGExec(),
    path
    );
}

ExecPortPtr Executable::getExecPort(uint32_t index)
{
  return ExecPort::Create(
    getDFGBinding(),
    getExecPath(),
    getDFGExec(),
    getDFGExec().getExecPortName( index )
    );
}

ExecPortPtr Executable::addExecPort(
  char const *title,
  FabricCore::DFGPortType portType,
  char const *dataType
  )
{
  return ExecPort::Create(
    getDFGBinding(),
    getExecPath(),
    getDFGExec(),
    getDFGExec().addExecPort(title, portType, dataType)
    );
}

void Executable::removeExecPort(char const * portPath)
{
  getDFGExec().removeExecPort( portPath );
}

void Executable::removeExecPort(uint32_t index)
{
  getDFGExec().removeExecPort( index );
}

void Executable::attachPreset(char const *parentPresetPath, char const *desiredName)
{
  getDFGExec().attachPreset(parentPresetPath, desiredName);
}
