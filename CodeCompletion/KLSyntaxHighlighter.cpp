// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLSyntaxHighlighter.h"

using namespace FabricServices;
using namespace FabricServices::CodeCompletion;

KLSyntaxHighlighter::KLSyntaxHighlighter(const FabricCore::Client * client)
{
  m_manager = new ASTWrapper::KLASTManager(client);
  m_owningManager = true;
  initRules();
}

KLSyntaxHighlighter::KLSyntaxHighlighter(ASTWrapper::KLASTManager * manager)
{
  m_manager = manager;
  m_owningManager = false;
  initRules();
}

KLSyntaxHighlighter::~KLSyntaxHighlighter()
{
  if(m_owningManager && m_manager)
    delete(m_manager);
}

void KLSyntaxHighlighter::initRules()
{
  // comment rules
  addRule(HighlightRuleType_Comment, "/\\*.*\\*/");
  addRule(HighlightRuleType_Comment, "//[^\n]*");

  // string rules
  addRule(HighlightRuleType_String, "\\\"([^\\\"]|\\\\.)*\\\"");
  addRule(HighlightRuleType_String, "'([^']|\\\\.)*'");

  // keyword rules
  addRule(HighlightRuleType_Keyword, "<<<");
  addRule(HighlightRuleType_Keyword, ">>>");
  addRule(HighlightRuleType_Keyword, "\\babs\\b");
  addRule(HighlightRuleType_Keyword, "\\bacos\\b");
  addRule(HighlightRuleType_Keyword, "\\basin\\b");
  addRule(HighlightRuleType_Keyword, "\\batan\\b");
  addRule(HighlightRuleType_Keyword, "\\bbreak\\b");
  addRule(HighlightRuleType_Keyword, "\\bconst\\b");
  addRule(HighlightRuleType_Keyword, "\\bcontinue\\b");
  addRule(HighlightRuleType_Keyword, "\\bcos\\b");
  addRule(HighlightRuleType_Keyword, "\\bcreateArrayGenerator\\b");
  addRule(HighlightRuleType_Keyword, "\\bcreateConstValue\\b");
  addRule(HighlightRuleType_Keyword, "\\bcreateReduce\\b");
  addRule(HighlightRuleType_Keyword, "\\bcreateValueGenerator\\b");
  addRule(HighlightRuleType_Keyword, "\\belse\\b");
  addRule(HighlightRuleType_Keyword, "\\bfor\\b");
  addRule(HighlightRuleType_Keyword, "\\bfunction\\b");
  addRule(HighlightRuleType_Keyword, "\\bif\\b");
  addRule(HighlightRuleType_Keyword, "\\bin\\b");
  addRule(HighlightRuleType_Keyword, "\\bio\\b");
  addRule(HighlightRuleType_Keyword, "\\boperator\\b");
  addRule(HighlightRuleType_Keyword, "\\breport\\b");
  addRule(HighlightRuleType_Keyword, "\\breturn\\b");
  addRule(HighlightRuleType_Keyword, "\\bsetError\\b");
  addRule(HighlightRuleType_Keyword, "\\bsin\\b");
  addRule(HighlightRuleType_Keyword, "\\bsqrt\\b");
  addRule(HighlightRuleType_Keyword, "\\binterface\\b");
  addRule(HighlightRuleType_Keyword, "\\bobject\\b");
  addRule(HighlightRuleType_Keyword, "\\bstruct\\b");
  addRule(HighlightRuleType_Keyword, "\\btan\\b");
  addRule(HighlightRuleType_Keyword, "\\btype\\b");
  addRule(HighlightRuleType_Keyword, "\\brequire\\b");
  addRule(HighlightRuleType_Keyword, "\\btrue\\b");
  addRule(HighlightRuleType_Keyword, "\\bfalse\\b");
  addRule(HighlightRuleType_Keyword, "\\bValueProducer\\b");
  addRule(HighlightRuleType_Keyword, "\\bwhile\\b");

  // ask the ast manager for all basic types
  const FabricCore::Client * client = m_manager->getClient();
  FabricCore::Variant registeredTypes = FabricCore::GetRegisteredTypes_Variant(*client);
  for(FabricCore::Variant::DictIter keyIter(registeredTypes); !keyIter.isDone(); keyIter.next())
  {
    std::string key = keyIter.getKey()->getStringData();
    if(key.substr(key.length()-1, 1) == ">")
      continue;
    if(GetRegisteredTypeIsStruct(*client, key.c_str()))
      continue;
    if(GetRegisteredTypeIsObject(*client, key.c_str()))
      continue;
    if(GetRegisteredTypeIsInterface(*client, key.c_str()))
      continue;
    addRule(HighlightRuleType_Type, "\\b"+key+"\\b");
  }
}

std::vector<SyntaxHighlighter::Format> KLSyntaxHighlighter::getHighlightFormats(const std::string & text, const std::string & fileName) const
{
  // todo: feed the text through the ast, and look for requires....
  return SyntaxHighlighter::getHighlightFormats(text);
}
