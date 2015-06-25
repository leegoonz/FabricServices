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
        char const *jsonData,
        uint32_t jsonSize,
        FabricCore::RTVal &rtVal
        )
      {
        try
        {
          if(!rtVal.isValid())
            return false;
          if(!rtVal.isObject())
            return false;

          FabricCore::RTVal cast = FabricCore::RTVal::Create(context, "RTValFromJSONDecoder", 1, &rtVal);
          if(!cast.isValid())
            return false;

          FabricCore::RTVal data = FabricCore::RTVal::ConstructString(context, jsonData, jsonSize);
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
