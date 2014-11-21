// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __Commands_CommandStack__
#define __Commands_CommandStack__

#include "Command.h"

#include <stdint.h>

namespace FabricServices
{

  namespace Commands
  {

    class CommandStack
    {
    public:

      CommandStack();
      virtual ~CommandStack();

      uint32_t getLimit() const;
      void setLimit(uint32_t limit);

      virtual bool add(Command * command);
      virtual void clear();
      virtual bool undo();
      virtual bool redo();

    private:

      void capCommandsForLimit();

      uint32_t m_limit;
      CommandVector m_undoCommands;
      CommandVector m_redoCommands;
    };

  };

};

#endif // __Commands_CommandStack__
