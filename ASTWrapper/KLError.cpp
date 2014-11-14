// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#include "KLError.h"
#include "KLError.h"

#include <boost/regex.hpp>

using namespace FabricServices::ASTWrapper;

boost::regex g_KLError_expr("(.*):([0-9]+):([0-9]+): (.*)$");

KLError::KLError(const char * message)
{
  std::string messageStr(message);
  boost::match_results<std::string::const_iterator> results;
  if (boost::regex_match(messageStr, results, g_KLError_expr))
  {
    m_fileName = results[1];
    m_line = atoi(std::string(results[2]).c_str());
    m_column = atoi(std::string(results[3]).c_str());
    m_description = results[4];
    m_valid = true;
  }
  else
  {
    m_valid = false;
  }
}

KLError::~KLError()
{
}

bool KLError::isValid() const
{
  return m_valid;
}

const char * KLError::getFileName() const
{
  return m_fileName.c_str();
}

int KLError::getLine() const
{
  return m_line;
}

int KLError::getColumn() const
{
  return m_column;
}

const char * KLError::getDescription() const
{
  return m_description.c_str();
}

