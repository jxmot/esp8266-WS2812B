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
#ifndef _SIGNCHANNEL
        Serial.println(String(__func__) + " size of channelcfg - " + String(sizeof(channelcfg)));
#else
        Serial.println(String(__func__) + " size of Channel - " + String(sizeof(Channel)));
#endif
//        Serial.println(buf.get());
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
    for(int idx_chan = 0; json["channels"][idx_chan]["index"] != -1; idx_chan++)
    {
        if(!muteDebug) Serial.println(String(__func__) + " name = " + String((const char *)json["channels"][idx_chan]["name"]));

#ifndef _SIGNCHANNEL
        channelcfg config;
#else
        Channel config;
#endif

        config.index    = json["channels"][idx_chan]["index"];
        config.name     = String((const char *)json["channels"][idx_chan]["name"]);
        config.action   = String((const char *)json["channels"][idx_chan]["action"]);
        config.duration = json["channels"][idx_chan]["duration"];
        config.end_hang = json["channels"][idx_chan]["end_hang"];

#ifndef _SIGNCHANNEL
        for(int ix = 0;ix < 3;ix++) config.default_color[ix] = json["channels"][idx_chan]["default_color"][ix];

        for(int ix = 0;ix < MAX_COLOR_STEPS;ix++) 
        {
            for(int iy = 0;iy < 3;iy++) config.color_list[ix][iy] = json["channels"][idx_chan]["color_list"][ix][iy];
            if(config.color_list[ix][0] == -1) break;
        }
#else
        config.default_color = MAKERGB(json["channels"][idx_chan]["default_color"]);

        for(int ix = 0;(ix < MAX_COLOR_STEPS) && (json["channels"][idx_chan]["color_list"][ix][0] != -1);ix++) 
        {
            RgbColor tmp = MAKERGB(json["channels"][idx_chan]["color_list"][ix]);
            config.color_list.emplace_back(tmp);
        }
#endif
        //v_channels.push_back(config);
        v_channels.emplace_back(config);
    }
    if(!muteDebug) Serial.println(String(__func__) + " v_channels size = " + String(v_channels.size()));
}

int  ChannelCfgData::getChanQty()
{
    return v_channels.size();
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



