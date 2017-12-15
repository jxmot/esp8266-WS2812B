

#pragma once

#include <NeoPixelBus.h>
#include <NeoPixelAnimator.h>

#include "SignCfgData.h"

#include "SignChannel.h"

#define DEFAULT_PIXEL_COUNT 16

class Sign
{
    public:
        Sign(const char *cfgfile, bool muted = true);
        ~Sign();

    private:
        bool muteDebug;

        SignCfgData *cfgdat;

        signcfg config;

        bool configSign(const char *cfgfile);
        void printSignCfg();

        bool configChannels(const char *cfgfile);

        NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> *strip;
        NeoPixelAnimator *animations;

        void initStrip(int pxCount = DEFAULT_PIXEL_COUNT);


};