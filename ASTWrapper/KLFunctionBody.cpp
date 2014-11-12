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
  parseCompoundStatement(data);
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

void KLFunctionBody::parseStatement(JSONData data)
{
  JSONData statementTypeVar = data->getDictValue("statementType");
  if(!statementTypeVar)
    return;

  std::string statementType = statementTypeVar->getStringData();
  
  if(statementType == "VarDeclStatement")
  {
    KLVariable * variable = new KLVariable(getKLFile(), data);
    m_variables.push_back(variable);
  }
  else if(statementType == "CompoundStatement")
  {
    parseCompoundStatement(data);
  }
  else if(statementType == "SwitchStatement")
  {
    parseSwitchStatement(data);
  }
  else if(statementType == "ConditionalStatement")
  {
    parseConditionalStatement(data);
  }
  else if(statementType == "CStyleLoop")
  {
    parseLoopStatement(data);
  }

}

void KLFunctionBody::parseCompoundStatement(JSONData data)
{
  JSONData statements = data->getDictValue("statements");
  if(statements)
  {
    for(uint32_t i=0;i<statements->getArraySize();i++)
    {
      JSONData statement = statements->getArrayElement(i);
      parseStatement(statement);
    }
  }  
}

void KLFunctionBody::parseSwitchStatement(JSONData data)
{
  JSONData cases = data->getDictValue("cases");
  if(cases)
  {
    for(uint32_t i=0;i<cases->getArraySize();i++)
    {
      JSONData statement = cases->getArrayElement(i);
      parseCompoundStatement(statement);
    }
  }
}

void KLFunctionBody::parseConditionalStatement(JSONData data)
{
  JSONData trueStatement = data->getDictValue("trueStatement");
  if(trueStatement)
    parseStatement(trueStatement);
  JSONData falseStatement = data->getDictValue("falseStatement");
  if(falseStatement)
    parseStatement(falseStatement);
}

void KLFunctionBody::parseLoopStatement(JSONData data)
{
  JSONData body = data->getDictValue("body");
  if(body)
    parseStatement(body);
}

