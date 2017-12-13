

#pragma once

#include <NeoPixelBus.h>
#include <NeoPixelAnimator.h>

#include "SignChannel.h"

#define DEFAULT_PIXEL_COUNT 16

class Sign
{
    public:
        Sign();
        ~Sign();

    private:
        NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> *strip;
        NeoPixelAnimator *animations;

        void initStrip(int pxCount = DEFAULT_PIXEL_COUNT);
};