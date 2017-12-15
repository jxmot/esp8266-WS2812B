
// required include files...
#include "src/applib/esp8266-ino.h"
#include "src/applib/esp8266-udp.h"

#include "Sign.h"

#ifdef __cplusplus
extern "C" {
#endif

bool configChannels();
bool configScripts();


void startSign()
{
    // initialize sign

    // read config & init - 
    //      channel settings
    //      scripts

    // begin initial state
}

bool configChannels()
{
    // read channel config and save
    // if successfull return true
}

bool configScripts()
{
    // read scripts config and save
    // if successfull return true
}

#ifdef __cplusplus
}
#endif

