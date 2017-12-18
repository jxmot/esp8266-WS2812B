#pragma once

#include "vector"

#include "SignColors.h"

#define MAX_COLOR_STEPS 16

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

class Channel 
{
    public:
        unsigned int index = channel_none;
        String name = "";
        String action = "";
        int duration = -1;
        int end_hang = -1;

        RgbColor default_color = DEFAULT_COLOR;
        RgbColor current_color = DEFAULT_COLOR;
        RgbColor next_color    = DEFAULT_COLOR;

//        RgbColor colorList[MAX_COLOR_STEPS];
        std::vector<RgbColor> color_list;
};

class SignChannel 
{
    public:
        SignChannel();
        ~SignChannel();

    private:
        Channel chann;
};

