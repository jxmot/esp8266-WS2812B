/* ************************************************************************ */
/*
    ChannelCfgData.cpp - Intended to provide external server configuration data. 

*/
#include "ChannelCfgData.h"
#include <ArduinoJson.h>

//////////////////////////////////////////////////////////////////////////////
/*
*/
ChannelCfgData::ChannelCfgData(const char *cfgfile, bool muted): ConfigData(cfgfile)
{
    muteDebug = muted;

    if(!muteDebug) Serial.println(String(__func__) + " - constructor");
}

//////////////////////////////////////////////////////////////////////////////
/*
*/
void ChannelCfgData::parseJSON(std::unique_ptr<char[]>& buf)
{
    if(!muteDebug)
    {
        Serial.println();
        Serial.println(String(__func__) + " parsing JSON - ");
        Serial.println(buf.get());
        Serial.println();
        Serial.flush();
    }
 
    // https://bblanchon.github.io/ArduinoJson/assistant/
    // 
    const size_t bufferSize = 44*JSON_ARRAY_SIZE(3) + JSON_ARRAY_SIZE(4) + 4*JSON_ARRAY_SIZE(10) + JSON_OBJECT_SIZE(1) + 4*JSON_OBJECT_SIZE(7) + 3694;
    //StaticJsonBuffer<bufferSize> jsonBuffer;
    DynamicJsonBuffer jsonBuffer(bufferSize);

    JsonObject& json = jsonBuffer.parseObject(buf.get());

    /*
        This is one of the places where you would customize this class to be 
        used with your application specific configuration data.
        
        Another place is in ChannelCfgData.h
    */

    if(!muteDebug)
    {
        int idx_chan = 0;
    
        while(json["channels"][idx_chan]["index"] != -1)
        {
            Serial.println("name = " + String((const char *)json["channels"][idx_chan++]["name"]));
        }
    }

    
}

//////////////////////////////////////////////////////////////////////////////
/*
    This is one of the places where you would customize this class to be 
    used with your application specific configuration data.
    
    Another place is in ChannelCfgData.h
*/
bool ChannelCfgData::getChanCfg(channelcfg &cfgout)
{

    return true;
}



