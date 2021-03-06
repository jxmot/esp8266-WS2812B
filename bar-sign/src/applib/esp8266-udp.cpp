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

// read & write buffers
unsigned char readBuffer[UDP_PAYLOAD_SIZE_READ];
unsigned char writeBuffer[UDP_PAYLOAD_SIZE_WRITE];

// Arduino UDP object
WiFiUDP udp;

/* ************************************************************************ */
/*
    Obtains the UDP configuration data, apply it and do any other necessary
    UDP config steps...
*/
int initUDP()
{
// a single server configuration
srvcfg udpServer;

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
    Send a payload to a multi-cast address
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

