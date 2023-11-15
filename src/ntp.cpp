#include <WiFiUdp.h>
#include <NTPClient.h>
#include "ntp.h"

WiFiUDP ntpUDP;

// EST offset (seconds). unused
// const long utcOffset = NTP_UTCOFFSET;
NTPClient timeClient(ntpUDP, NTP_POOL);
