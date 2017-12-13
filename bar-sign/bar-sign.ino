

#include <NeoPixelBus.h>

#include "bar-sign.h"

void setup()
{
    Serial.begin(115200);
    while (!Serial);

    Serial.println();
    Serial.println("Initializing...");
    Serial.flush();

    //initStrip();

    // read config

    // init wifi

    // init UDP server

    Serial.println();
    Serial.println("Running...");
}

void loop()
{

}


