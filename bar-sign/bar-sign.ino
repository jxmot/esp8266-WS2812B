/* ************************************************************************ */
/*
    bar-sign.ino - An ESP8266 project that is a repurposing of an old bar
    back sign. Which is a piece of clear plastic that was originally edge
    lit with incandesant bulbs. The four bulbs have been replaced with
    WS2812B RGB LEDs. This code will control them based on commands that
    it receives.
*/

// required include files...
#include "src/applib/esp8266-ino.h"
#include "src/applib/esp8266-udp.h"

#include "bar-sign.h"

/* ************************************************************************ */
/*
    Application Set Up
*/
void setup()
{
    setupStart();

    setupConfig();

    setupInit();

    // initial setup is complete, wrap up and continue...
    setupDone();
}

/*
    Application Execution Loop
*/
void loop()
{
    yield();

    if(toggInterv == ERR_TOGGLE_INTERVAL)
    {
        // stop animations and turn off LEDs...

        // wait now before proceeding...
        delay(toggInterv);

        toggleLED();
    }
    else
    {
        handleComm();

        //handleDisplay();
    }
}


