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
        uint16_t duration = 0;
        int end_hang = -1;

// NOTES:
// RE: HSL colors, the library has an odd requirement
// for specifying the HSL values - 
//  hue - 0 to 360 = 0.0f to 1.0f
//  sat - 0 to 100 = 0.0f to 1.0f
//  lum - 0 to 100 = 0.0f to 0.5f
//
// to convert stored hue values to library values - 
//  library hue = stored hue * 0.002777
//      hue = 114 * 0.002777 = 0.316578
//
// to convert sat and lum = 
//  sat = 57 * .01
//  lum = 65 * .005

        RgbColor default_color = DEFAULT_COLOR;
        RgbColor current_color = DEFAULT_COLOR;
        RgbColor next_color    = DEFAULT_COLOR;

//        RgbColor colorList[MAX_COLOR_STEPS];
        std::vector<RgbColor> color_list;
};

/*
class SignChannel 
{
    public:
        SignChannel();
        ~SignChannel();

    private:
        Channel chann;
};

*/

