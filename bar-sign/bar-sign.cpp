#include "bar-sign.h"

#include "SignChannel.h"

// three element pixels, in different order and speeds
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

BarSign::BarSign()
{
    initStrip();

    // read config - 
    //      channel settings
    //      scripts

    // begin initial state
}

void BarSign::initStrip()
{
    // this resets all the neopixels to an off state
    strip.Begin();
    strip.Show();
}

bool BarSign::configChannels()
{
    // read channel config and save
    // if successfull return true
};

bool BarSign::configScripts()
{
    // read scripts config and save
    // if successfull return true
};

/*
bool BarSign::
bool BarSign::
bool BarSign::

*/

