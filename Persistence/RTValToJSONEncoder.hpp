// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __Persistence_RTValToJSONEncoder__
#define __Persistence_RTValToJSONEncoder__

#include <vector>
#include <string>
#include <FabricCore.h>
#include <FTL/CStrRef.h>

namespace FabricServices
{

  namespace Persistence
  {
    
    class RTValToJSONEncoder : public FabricCore::RTValToJSONEncoder
    {

    public:

      virtual bool encodeRTValToJSON(
        FabricCore::Context const &context,
        FabricCore::RTVal const &rtVal,
        FabricCore::RTValToJSONEncoder::AppendFunctor const &append
        )
      {
        try
        {
          if(!rtVal.isValid())
            return false;
          if(!rtVal.isObject())
            return false;
          if(rtVal.isNullObject())
            return false;

          FabricCore::RTVal cast = FabricCore::RTVal::Construct(context, "RTValToJSONEncoder", 1, &rtVal);
          if(!cast.isValid())
            return false;
          if(cast.isNullObject())
            return false;
          
          FabricCore::RTVal result = cast.callMethod("String", "convertToString", 0, 0);
          if(!result.isValid())
            return false;

          FTL::CStrRef ref = result.getStringCString();
          if(ref.size() == 0)
            return false;
          
          append("\"");
          append(ref.c_str());
          append("\"");
          return true;
        }
        catch(FabricCore::Exception e)
        {
          printf("encodeRTValToJSON: Hit exception: %s\n", e.getDesc_cstr());
        }
        return false;
      }

    };

  };

};

#endif // __Persistence_RTValToJSONEncoder__
