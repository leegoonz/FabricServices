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
          printf("decodeRTValFromJSON\n");

          if(!rtVal.isValid())
          {
            printf("not valid\n");
            return false;
          }
          if(!rtVal.isObject())
          {
            printf("not an object\n");
            return false;
          }

          FabricCore::RTVal cast = FabricCore::RTVal::Construct(context, "RTValFromJSONDecoder", 1, &rtVal);
          if(!cast.isValid())
          {
            printf("cast failed\n");
            return false;
          }

          printf("we have cast...\n");

          if(jsonSize <= 2)
            return false;

          printf("we have a string...\n");

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
