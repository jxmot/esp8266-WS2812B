/* ************************************************************************ */
/*
    SignCfgData.cpp - Intended to provide external server configuration data. 

*/
#include "SignCfgData.h"
#include <ArduinoJson.h>

//////////////////////////////////////////////////////////////////////////////
/*
*/
SignCfgData::SignCfgData(const char *cfgfile, bool muted): ConfigData(cfgfile)
{
    muteDebug = muted;

    if(!muteDebug) Serial.println(String(__func__) + " - constructor");
}

//////////////////////////////////////////////////////////////////////////////
/*
*/
void SignCfgData::parseJSON(std::unique_ptr<char[]>& buf)
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
    // {"channels":4,"channcfg":"/channelcfg.dat","leftchann": 0}
    const size_t bufferSize = JSON_OBJECT_SIZE(3) + 101;
    StaticJsonBuffer<bufferSize> jsonBuffer;

    JsonObject& json = jsonBuffer.parseObject(buf.get());

    /*
        This is one of the places where you would customize this class to be 
        used with your application specific configuration data.
        
        Another place is in SignCfgData.h
    */
    config.channels  = json["channels"];
    config.channcfg  = String((const char*)json["channcfg"]);
    config.leftchann = json["leftchann"];
}

//////////////////////////////////////////////////////////////////////////////
/*
    This is one of the places where you would customize this class to be 
    used with your application specific configuration data.
    
    Another place is in SignCfgData.h
*/
bool SignCfgData::getSignCfg(signcfg &cfgout)
{
    cfgout.channels  = config.channels;
    cfgout.channcfg  = config.channcfg;
    cfgout.leftchann = config.leftchann;
    return true;
}



