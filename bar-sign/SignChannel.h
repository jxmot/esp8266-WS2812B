#pragma once

#include "SignColors.h"

#define MAX_COLOR_STEPS 8

enum ChannelID
{
    channel_none = -1,
    channel_1 = 0,
    channel_2,
    channel_3,
    channel_4,
    channel_max,
    allChannels
};

struct Channel 
{
    unsigned int id = channel_none;

    RgbColor defaultColor = DEFAULT_COLOR;
    RgbColor currentColor = DEFAULT_COLOR;
    RgbColor nextColor    = DEFAULT_COLOR;

    RgbColor colorList[MAX_COLOR_STEPS];
};

class SignChannel 
{
    public:
        SignChannel(ChannelID chid){chann.id = chid;};
        ~SignChannel();

    private:
        Channel chann;
};

