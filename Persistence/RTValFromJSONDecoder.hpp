// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __Persistence_RTValFromJSONDecoder__
#define __Persistence_RTValFromJSONDecoder__

#include <vector>
#include <string>
#include <FabricCore.h>
#include <FTL/JSONDec.h>

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

          std::string decodedString;
          {
            FTL::StrRef jsonStr( jsonData, jsonSize );
            FTL::JSONStrWithLoc strWithLoc( jsonStr );
            FTL::JSONDec jsonDec( strWithLoc );
            FTL::JSONEnt jsonEnt;
            if ( !jsonDec.getNext( jsonEnt )
              || jsonEnt.getType() != jsonEnt.Type_String )
              return false;
            jsonEnt.stringAppendTo( decodedString );
          }

          FabricCore::RTVal cast = FabricCore::RTVal::Construct(context, "RTValFromJSONDecoder", 1, &rtVal);
          if(!cast.isInterface())
            return false;
          if(cast.isNullObject())
            return false;

          FabricCore::RTVal data =
            FabricCore::RTVal::ConstructString(
              context,
              decodedString.data(),
              decodedString.size()
              );
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
