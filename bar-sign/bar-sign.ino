/* ************************************************************************ */
/*
    bar-sign.ino - An ESP8266 project that is a repurposing of an old bar
    back sign. Which is a piece of clear plastic that was originally edge
    lit with incandesant bulbs. The four bulbs have been replaced with
    WS2812B RGB LEDs. This code will control them based on commands that
    it receives.
*/

// If defined then enable "demonstration mode" operations. This includes the
// use of demo-configuration files instead of the ones with sensitive info.
//#define CONFIG_DEMO

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

    if(setupApp("/appcfg.dat")) 
    {
#ifdef CONFIG_DEMO
        if(setupWiFi("/wificfg.dat")) 
        {
            if(!setupServers("/servercfg.dat")) toggInterv = ERR_TOGGLE_INTERVAL;
        } else toggInterv = ERR_TOGGLE_INTERVAL;
#else
        // NOTE: The .gitignore in this repo is configured to ignore ALL
        // files that start with an underscore ('_'). This allows for
        // versions of these files that contain "sensitive" information
        // to be ignored by git. The reason that there are two copies of 
        // this code block is to serve as a gentle reminder that there can
        // be additional differences between modes. For example, some config 
        // operations might not be necessary in CONFIG_DEMO.
        if(setupWiFi("/_wificfg.dat")) 
        {
            if(!setupServers("/_servercfg.dat")) toggInterv = ERR_TOGGLE_INTERVAL;
        } else toggInterv = ERR_TOGGLE_INTERVAL;
#endif
    } else  toggInterv = ERR_TOGGLE_INTERVAL;

    // initial setup is complete, wrap up and continue...
    setupDone();

    // if we're not indicating an error the continue with the 
    // initialization of the UDP functionality...
    if(toggInterv == TOGGLE_INTERVAL) 
    {
        if(!initUDP()) 
        {
            printError(String(__func__), "UDP init failed!");
            toggInterv = ERR_TOGGLE_INTERVAL;
        }
    }

    // instantiate a sign object...

    // running...
    Serial.println();
    Serial.println("Running...");
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
        handleUDP();
    }
}


