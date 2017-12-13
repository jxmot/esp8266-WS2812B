
#include "Sign.h"


Sign::Sign()
{
    strip = NULL;
    animations = NULL;
}

Sign::~Sign()
{
    delete strip;
    delete animations;
}

void Sign::initStrip(int pxCount/* = DEFAULT_PIXEL_COUNT*/)
{
    if(strip != NULL) delete strip;

    strip = new NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>(pxCount);

    // this resets all the neopixels to an off state
    strip->Begin();
    strip->Show();
}
