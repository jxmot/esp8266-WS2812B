/* ************************************************************************ */
/*
    SignCfgData.h - 

*/
#pragma once

#include "src/applib/ConfigData.h"

class signcfg
{
    public:
        int channels = 0;
        String channcfg;
        int leftchann = 0;
};

class SignCfgData : public ConfigData {

    public:
        SignCfgData(const char *cfgfile, bool muted = false);

    private:
        void parseJSON(std::unique_ptr<char[]>& buf) override;

    //////////////////////////////////////////////////////////////////////////
    /*
        This is one of the places where you would customize this class to be 
        used with your application specific configuration data.
        
        The other place is in SignCfgData.cpp
    */
    public:
        bool getSignCfg(signcfg &cfgout);

    private:
        bool muteDebug;
        signcfg config;
};

