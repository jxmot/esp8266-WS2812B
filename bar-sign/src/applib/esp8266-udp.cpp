/* ************************************************************************ */
/*
    esp8266-udp.cpp - UDP support for the associated ino file.
*/
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include "esp8266-ino.h"
#include "udp-defs.h"

#ifdef __cplusplus
extern "C" {
#endif

int replyUDP(char *payload, int len);
int recvUDP();

// The size (in bytes) of the UDP data that we're expecting 
// to exchange with the server. The +1 is a place holder 
// for a NULL if a string uses the full capacity of the
// buffer.
//
// NOTE: Things seem to work the best when the READ and
// WRITE sizes are the same.
#define UDP_PAYLOAD_SIZE_READ (UDP_PAYLOAD_SIZE + 1)
#define UDP_PAYLOAD_SIZE_WRITE (UDP_PAYLOAD_SIZE + 1)

// read & write buffers
unsigned char readBuffer[UDP_PAYLOAD_SIZE_READ];
unsigned char writeBuffer[UDP_PAYLOAD_SIZE_WRITE];

// Arduino UDP object
WiFiUDP udp;

// a single server configuration
srvcfg udpServer;

// the test data (a string) that we'll send to the server
char *testReply = "GOT it!!! 1 2 3 4\00";


/* ************************************************************************ */
/*
    Obtains the UDP configuration data, apply it and do any other necessary
    UDP config steps...
*/
int initUDP()
{
bool success = false;
int iRet = 0;

    // make sure the WiFi is connected...
    if((connWiFi != NULL) && connWiFi->IsConnected())
    {
        // init the UDP...
        s_cfgdat->getServerCfg("udp", udpServer);
        if(udp.begin(udpServer.port)) success = true;
    }
    if(!checkDebugMute()) Serial.println("initUDP() - success = " + String(success));

    if(success) iRet = UDP_PAYLOAD_SIZE;
    else iRet = 0;

    return iRet;
}

/*
*/
int handleUDP()
{
int sent = 0;
int rcvd = 0;
String temp;

    rcvd = recvUDP();

    if((rcvd <= UDP_PAYLOAD_SIZE) && (rcvd > 0))
    {
        // decode the UDP payload contents

        // act on the contents

        // reply to the contents...

        // a "test" reply, comment out later
        sent = replyUDP(testReply, strlen(testReply));

        // if debug mute is off then show some info...
        if(!checkDebugMute())
        {
            Serial.println();
            Serial.println("handleUDP() - rcvd = " + String(rcvd));
    
            // NOTE: It was assumed that the UDP packet contained a 
            // string of characters. The string could contain anything 
            // (up to udp-defs.h:UDP_PAYLOAD_SIZE bytes in size) even
            // a JSON string. The string MUST be NULL terminated, there's 
            // more info in esp8266-udp.cpp
            temp = String((char *)&readBuffer[0]);
    
            Serial.println("handleUDP() - data = " + temp);
            Serial.println();
            Serial.println("handleUDP() - sent  = " + String(sent));
            // a "test" reply, comment or change out later
            Serial.println("handleUDP() - reply = " + String(testReply));
            Serial.println();
            Serial.flush();
        }
    } else if(rcvd)
    {
        printError(String(__func__), "UDP received packet too long - " + String(rcvd));
        printError(String(__func__), "Setting error state.");
        toggInterv = ERR_TOGGLE_INTERVAL;            
    }
    return rcvd;
}


/*
    Reply with a UDP packet...
*/
int replyUDP(char *payload, int len)
{
int iRet = 0;

    if(!checkDebugMute()) Serial.println("replyUDP() - len = " + String(len));

    // set the entire write buffer contents to 0
    memset(writeBuffer, 0, UDP_PAYLOAD_SIZE_WRITE);

    // if the length of payload is valid then
    // assemble the UDP packet...
    if((len < UDP_PAYLOAD_SIZE_WRITE) && (len > 0))
    {
        // copy the payload into the write buffer
        memcpy(writeBuffer, payload, len);

        // "begin" the UDP packet...
        udp.beginPacket(udp.remoteIP(), udp.remotePort());
    
        // write & send the UDP packet...
        iRet = udp.write(writeBuffer, len);

        if(!checkDebugMute()) Serial.println("replyUDP("+String(iRet)+") - reply to " + IPAddress(udp.remoteIP()).toString() + ":" + udp.remotePort());
    
        // finish & send the packet
        if(udp.endPacket() == 0) iRet = -1;
    }
    return iRet;
}

/*
    If a UDP packet was received then read it and place it
    in the read buffer & return the length of the data read.
*/
int recvUDP()
{
int packetLen;
int readLen = 0;

    // begins processing a packet if one is available
    if(packetLen = udp.parsePacket())
    {
        // clear the read buffer
        memset(readBuffer, 0, UDP_PAYLOAD_SIZE_READ);

        if(packetLen < UDP_PAYLOAD_SIZE)
        {
            // read the payload
            readLen = udp.read(readBuffer, packetLen);
        } else readLen = packetLen;
    }
// to noisy...
//    if(!checkDebugMute()) Serial.println("recvUDP() - packetLen = " + String(packetLen) + "  readLen = " + readLen);
    return readLen;
}

/*
*/
int multiUDP(char *payload, int len)
{
mcastcfg cfg;

    if(m_cfgdat->getCfg(cfg))
    {
        udp.beginPacketMulticast(cfg.ipaddr, cfg.port, WiFi.localIP());
        udp.write(payload, len);
        udp.endPacket();
    }
}

#ifdef __cplusplus
}
#endif

