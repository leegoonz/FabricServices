// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __ASTWrapper_KLStatement__
#define __ASTWrapper_KLStatement__

#include "KLCommented.h"
#include "KLStatementSearch.h"

#include <string>

namespace FabricServices
{

  namespace ASTWrapper
  {

    class KLStatement : public KLCommented, public KLStatementSearch
    {
    public:

      virtual ~KLStatement();

      virtual KLDeclType getDeclType() const;
      virtual bool isOfDeclType(KLDeclType type) const;

      std::string getTypeName() const;

      virtual uint32_t getChildCount() const;
      virtual const KLStatement * getChild(uint32_t index) const;
      virtual const KLStatement * getParent() const;
      virtual const KLStatement * getTop() const;
      virtual uint32_t getDepth() const;

      virtual std::vector<const KLStatement*> getAllChildrenOfType(KLDeclType type, bool downwards = false, bool upwards = false) const;

      virtual const KLStatement * getStatementAtCursor(uint32_t line, uint32_t column) const;
      virtual uint32_t getCursorDistance(uint32_t line, uint32_t column) const;

    protected:

      KLStatement(const KLFile* klFile, JSONData data, KLStatement * parent = NULL);
      const KLStatement * constructChild(JSONData data);

      std::string m_type;
      KLStatement * m_parent;
      uint32_t m_depth;
      std::vector<KLStatement*> m_statements;
    };

  };

};


#endif // __ASTWrapper_KLStatement__
