
#include "Sign.h"
#include "esp8266-ino.h"


Sign::Sign(const char *cfgfile, bool muted/* = true*/)
{
    muteDebug = muted;

    strip = NULL;
    animations = NULL;

    // read config & init - 
    if(configSign(cfgfile))
    {
        // channel settings
        configChannels(config.channcfg);
    }

    //      scripts

}

Sign::~Sign()
{
    delete strip;
    delete animations;
    delete cfgdat;
}

bool Sign::configSign(const char *cfgfile)
{
String errMsg;
String func = String(__func__);
bool bRet = false;

    // get the config data...
    cfgdat = new SignCfgData(cfgfile, muteDebug);

    // check for errors
    if(!cfgdat->getError(errMsg)) 
    {
        // success, parse the JSON string
        cfgdat->parseFile();

        // check for errors
        if(cfgdat->getError(errMsg)) printError(func, errMsg);
        else 
        {
            cfgdat->getSignCfg(config);

            // success, display the config data
            printSignCfg();
            bRet = true;
        }
    } else printError(func, errMsg);

    return bRet;
}

void Sign::printSignCfg()
{
    if(!muteDebug)
    {
        Serial.println(String(__func__) + " - config = ");
        Serial.println("    channels  : " + String(config.channels));
        Serial.println("    channcfg  : " + config.channcfg);
        Serial.println("    leftchann : " + String(config.leftchann));
        Serial.println();
    }
}

bool Sign::configChannels(const char *cfgfile)
{
    // read channel config and save
    // if successfull return true
}


void Sign::initStrip(int pxCount/* = DEFAULT_PIXEL_COUNT*/)
{
    if(strip != NULL) delete strip;

    strip = new NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>(pxCount);

    // this resets all the neopixels to an off state
    strip->Begin();
    strip->Show();
}
