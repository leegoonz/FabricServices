// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __Persistence_RTValFromJSONDecoder__
#define __Persistence_RTValFromJSONDecoder__

#include <vector>
#include <string>
#include <FabricCore.h>

namespace FabricServices
{

  namespace Persistence
  {
    
    class RTValFromJSONDecoder : public FabricCore::RTValFromJSONDecoder
    {

    public:

      virtual bool decodeRTValFromJSON(
        FabricCore::Context const &context,
        FabricCore::RTVal &rtVal,
        char const *jsonData,
        uint32_t jsonSize
        )
      {
        if(jsonSize <= 2)
          return false;

        try
        {
          if(!rtVal.isValid())
            return false;
          if(!rtVal.isObject())
            return false;
          if(rtVal.isNullObject())
            return false;

          FabricCore::RTVal cast = FabricCore::RTVal::Construct(context, "RTValFromJSONDecoder", 1, &rtVal);
          if(!cast.isInterface())
            return false;
          if(cast.isNullObject())
            return false;

          // by reducing the string we are cutting off the two quotes
          FabricCore::RTVal data = FabricCore::RTVal::ConstructString(context, &jsonData[1], jsonSize-2);
          FabricCore::RTVal result = cast.callMethod("Boolean", "convertFromString", 1, &data);
          if(!result.isValid())
            return false;

          return result.getBoolean();
        }
        catch(FabricCore::Exception e)
        {
          printf("decodeRTValToJSON: Hit exception: %s\n", e.getDesc_cstr());
        }

        return false;
      }

    };

  };

};

#endif // __Persistence_RTValFromJSONDecoder__
