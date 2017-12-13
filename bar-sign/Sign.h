

#pragma once

#include <NeoPixelBus.h>

#define DEFAULT_PIXEL_COUNT 16

class Sign
{
    public:
        Sign();
        ~Sign();

    private:
        NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> *strip;

        void initStrip(int pxCount = DEFAULT_PIXEL_COUNT);
};