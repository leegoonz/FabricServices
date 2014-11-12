// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLFunctionBody.h"
#include "KLMethod.h"

#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>

using namespace FabricServices::ASTWrapper;

KLFunctionBody::KLFunctionBody(const KLFile* klFile, JSONData data)
: KLDecl(klFile, data)
{
  printf("%s\n", data->getJSONEncoding().getStringData());
 
  JSONData statements = getArrayDictValue("statements");
  if(statements)
  {
    for(uint32_t i=0;i<statements->getArraySize();i++)
    {
      JSONData statement = statements->getArrayElement(i);
      JSONData statementTypeVar = statement->getDictValue("statementType");
      if(!statementTypeVar)
        continue;

      std::string statementType = statementTypeVar->getStringData();
      
      if(statementType == "VarDeclStatement")
      {
        KLVariable * variable = new KLVariable(klFile, statement);
        m_variables.push_back(variable);
      }
    }
  }
}

KLFunctionBody::~KLFunctionBody()
{
  for(uint32_t i=0;i<m_variables.size();i++)
  {
    delete(m_variables[i]);
  }
}

uint32_t KLFunctionBody::getVariableCount() const
{
  return m_variables.size();
}

const KLVariable * KLFunctionBody::getVariable(uint32_t index) const
{
  return m_variables[index];
}
