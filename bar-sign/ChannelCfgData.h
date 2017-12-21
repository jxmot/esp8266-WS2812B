/* ************************************************************************ */
/*
    ChannelCfgData.h - 

*/
#pragma once

#include "vector"
#include "src/applib/ConfigData.h"

#include "SignChannel.h"
#define _SIGNCHANNEL


class channelcfg
{
    public:
        int index = -1;
        String name = "n/a";
        String action = "n/a";
        uint16_t duration = 0;
        int end_hang = -1;
        int default_color[3] = {0,0,0};
        int color_list[MAX_COLOR_STEPS][3];
};

class ChannelCfgData : public ConfigData {

    public:
        ChannelCfgData(const char *cfgfile, bool muted = false);

    private:
        void parseJSON(std::unique_ptr<char[]>& buf) override;

    //////////////////////////////////////////////////////////////////////////
    /*
        This is one of the places where you would customize this class to be 
        used with your application specific configuration data.
        
        The other place is in ChannelCfgData.cpp
    */
    public:
        int getChanQty();
        uint16_t getDuration(int idx);
        RgbColor getCurrColor(int idx);
        RgbColor getNextColor(int idx);

#ifndef _SIGNCHANNEL
        bool getChanCfg(channelcfg &cfgout);
#else
        bool getChanCfg(int index, Channel &cfgout);
#endif
    private:
        bool muteDebug;
#ifndef _SIGNCHANNEL
        std::vector<channelcfg> v_channels;
#else
        std::vector<Channel> v_channels;
#endif
};

