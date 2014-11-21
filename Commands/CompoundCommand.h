// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __Commands_CompoundCommand__
#define __Commands_CompoundCommand__

#include "Command.h"

namespace FabricServices
{

  namespace Commands
  {
    class CompoundCommand : public Command
    {
    public:

      CompoundCommand();
      virtual ~CompoundCommand();

      virtual const char * getName() const;
      virtual const char * getShortDesc() const;
      virtual const char * getFullDesc() const;

      virtual bool add(Command * command);
      virtual bool isEmpty() const;

    protected:
      
      virtual bool invoke();
      virtual bool undo();
      virtual bool redo();
      virtual void destroy(); 

    private:

      CommandVector m_commands;
    };

  };

};

#endif // __Commands_CompoundCommand__
