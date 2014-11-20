// Copyright 2010-2014 Fabric Engine Inc. All rights reserved.

#ifndef __Commands_Command__
#define __Commands_Command__

namespace FabricServices
{

  namespace Commands
  {
    class Command
    {
      friend class CommandStack;

    public:

      Command();
      virtual ~Command();

      virtual const char * getName() const = 0;
      virtual const char * getShortDesc() const = 0;
      virtual const char * getFullDesc() const = 0;

    protected:
      
      virtual bool invoke() = 0;
      virtual bool undo() = 0;
      virtual bool redo();
      virtual void destroy(); 
    };

  };

};

#endif // __Commands_Command__
