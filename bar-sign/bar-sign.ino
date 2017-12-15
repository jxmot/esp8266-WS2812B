/* ************************************************************************ */
/*
    bar-sign.ino - An ESP8266 project that is a re-purposing of an old bar
    back sign. Which is a piece of clear plastic that was originally edge
    lit with incandescent bulbs. The four bulbs have been replaced with
    WS2812B RGB LEDs. This code will control them based on commands that
    it receives.

    Intended Operation : 

    Basically the sign will have 4 channels. And each can be operated 
    independently. It will be up to the client(s) to select color, 
    brightness, and animations. This code will not interpret the "meanings"
    other than generic error indications.
*/

// required include files...
#include "esp8266-ino.h"

/* ************************************************************************ */
/*
    Application Set Up
*/
void setup()
{
    // begin the set up process...
    setupStart();
    // read and parse the necessary config files
    setupConfig();
    // initialize prior to running the application
    setupInit();
    // initial setup is complete, wrap up and continue...
    setupDone();
    // get the sign mcp running...
    //startSign();
}

/*
    Application Execution Loop
*/
void loop()
{
    yield();

    // NOTE: using the LED toggle interval value to indicate 
    // an error comes from a prior interation of this code. 
    // however this application only flashes the LED if an
    // error has non-recoverable occurred. such errors include :
    //      * missing or invalid config file(s)
    //      * a received UDP packet length exceeded the buffer size
    //      * could not initialize for UDP
    if(toggInterv == ERR_TOGGLE_INTERVAL)
    {
        // stop animations and turn off LEDs...
        //stopDisplay();

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


