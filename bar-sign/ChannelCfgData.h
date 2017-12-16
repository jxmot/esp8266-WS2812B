/* ************************************************************************ */
/*
    ChannelCfgData.h - 

*/
#pragma once

#include "vector"
#include "src/applib/ConfigData.h"

#include "SignChannel.h"

class channelcfg
{
    public:
        int index = -1;
        String name = "n/a";
        String action = "n/a";
        int duration = -1;
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
        bool getChanCfg(channelcfg &cfgout);

    private:
        bool muteDebug;
        //channelcfg config;

        std::vector<channelcfg> v_channels;
};

