
// required include files...
#include "esp8266-ino.h"
#include "Sign.h"

#ifdef __cplusplus
extern "C" {
#endif

bool configScripts();

Sign *barSign = NULL;

void startSign()
{
    // initialize sign
    barSign = new Sign("/signcfg.dat", checkDebugMute());

    // begin initial state
}


bool configScripts()
{
    // read scripts config and save
    // if successfull return true
}

#ifdef __cplusplus
}
#endif

