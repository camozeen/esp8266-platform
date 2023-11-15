#ifndef __NTP_H
#define __NTP_H

#include <WiFiUdp.h>
#include <NTPClient.h>

extern WiFiUDP ntpUDP;

extern NTPClient timeClient;

#endif // __NTP_H
