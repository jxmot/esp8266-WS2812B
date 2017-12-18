
#include "Sign.h"
#include "esp8266-ino.h"


Sign::Sign(const char *cfgfile, bool muted/* = true*/)
{
    muteDebug = muted;

    strip = NULL;
    animations = NULL;

/*
    configSign(cfgfile);

    configChannels("/channelcfg.dat");
*/
    // read config & init - 
    if(configSign(cfgfile))
    {
        // channel settings
        configChannels((const char *)s_config.channcfg.c_str());
    }
    //      scripts

}

Sign::~Sign()
{
    delete strip;
    delete animations;
    delete signcfgdat;
}

bool Sign::configSign(const char *cfgfile)
{
String errMsg;
String func = String(__func__);
bool bRet = false;

    // get the config data...
    signcfgdat = new SignCfgData(cfgfile, muteDebug);

    // check for errors
    if(!signcfgdat->getError(errMsg)) 
    {
        // success, parse the JSON string
        signcfgdat->parseFile();

        // check for errors
        if(signcfgdat->getError(errMsg)) printError(func, errMsg);
        else 
        {
            signcfgdat->getSignCfg(s_config);

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
        Serial.println("    channels  : " + String(s_config.channels));
        Serial.println("    channcfg  : " + s_config.channcfg);
        Serial.println("    leftchann : " + String(s_config.leftchann));
        Serial.println();
    }
}

bool Sign::configChannels(const char *cfgfile)
{
String errMsg;
String func = String(__func__);
bool bRet = false;

    // get the config data...
    chancfgdat = new ChannelCfgData(cfgfile, muteDebug);

    // check for errors
    if(!chancfgdat->getError(errMsg)) 
    {
        // success, parse the JSON string
        chancfgdat->parseFile();

        // check for errors
        if(chancfgdat->getError(errMsg)) printError(func, errMsg);
        else 
        {
            if(chancfgdat->getChanQty() > 0)
            {
                printChanCfg();
                bRet = true;
            }
        }
    } else printError(func, errMsg);

    return bRet;
}

void Sign::printChanCfg()
{
    if(!muteDebug)
    {
        Serial.println(String(__func__) + " - config = ");
//        Serial.println("    channels  : " + String(config.channels));
        Serial.println();
    }
}

void Sign::initStrip(int pxCount/* = DEFAULT_PIXEL_COUNT*/)
{
    if(strip != NULL) delete strip;

    strip = new NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>(pxCount);

    // this resets all the neopixels to an off state
    strip->Begin();
    strip->Show();
}
