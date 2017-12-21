
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
    delete chancfgdat;
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

            initStrip(s_config.channels);

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

/* ************************************************************************* */ 

void Sign::initStrip(int pxCount/* = DEFAULT_PIXEL_COUNT*/)
{
    if(strip != NULL) delete strip;

    strip = new NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>(pxCount);
    animations = new NeoPixelAnimator(pxCount);

    // this resets all the neopixels to an off state
    strip->Begin();
    strip->Show();
}

AnimUpdateCallback Sign::animChannel(const AnimationParam& param)
{
    RgbColor newcolor = RgbColor::LinearBlend(chancfgdat->getCurrColor(param.index),
                                              chancfgdat->getNextColor(param.index),
                                              param.progress);

    strip->SetPixelColor(param.index, newcolor);
}

void Sign::startChannel(uint16_t idx)
{
/*
    strip->SetPixelColor(idx, COLOR_BLACK);
    animations->StartAnimation(idx, chancfgdat->getDuration(idx), animChannel);
*/
}

