// Copyright 2010-2015 Fabric Software Inc. All rights reserved.

#ifndef __Persistence_RTValToJSONEncoder__
#define __Persistence_RTValToJSONEncoder__

#include <vector>
#include <string>
#include <FabricCore.h>
#include <FTL/CStrRef.h>
#include <FTL/JSONEnc.h>

namespace FabricServices
{

  namespace Persistence
  {
    
    class RTValToJSONEncoder : public FabricCore::RTValToJSONEncoder
    {

    public:

      virtual FabricCore::RTValCodecResult encodeRTValToJSON(
        FabricCore::Context const &context,
        FabricCore::RTVal const &rtVal,
        FabricCore::RTValToJSONEncoder::AppendFunctor const &append,
        FabricCore::RTValToJSONEncoder::MetadataLookupFunctor const &metadataLookup
        )
      {
        try
        {
          if(!rtVal.isValid())
            return FabricCore::RTValCodecResult_Accept_Pending;
          if(!rtVal.isObject())
            return FabricCore::RTValCodecResult_Accept_Pending;
          if(rtVal.isNullObject())
            return FabricCore::RTValCodecResult_Accept_Pending;

          FabricCore::RTVal cast = FabricCore::RTVal::Construct(context, "RTValToJSONEncoder", 1, &rtVal);
          if(!cast.isValid())
            return FabricCore::RTValCodecResult_Accept_Pending;
          if(cast.isNullObject())
            return FabricCore::RTValCodecResult_Accept_Pending;
          
          FabricCore::RTVal result = cast.callMethod("String", "convertToString", 0, 0);
          if(!result.isValid())
            return FabricCore::RTValCodecResult_Accept_Pending;

          FTL::CStrRef ref = result.getStringCString();
          if(ref.size() == 0)
            return FabricCore::RTValCodecResult_Accept_Pending;
          
          std::string json;
          {
            FTL::JSONEnc<> jsonEnc( json );
            FTL::JSONStringEnc<> jsonStringEnc( jsonEnc, ref );
          }

          append( json.c_str() );

          return FabricCore::RTValCodecResult_Accept_Complete;
        }
        catch(FabricCore::Exception e)
        {
          printf("encodeRTValToJSON: Hit exception: %s\n", e.getDesc_cstr());
        }
        return FabricCore::RTValCodecResult_Accept_Pending;
      }

    };

  };

};

#endif // __Persistence_RTValToJSONEncoder__
