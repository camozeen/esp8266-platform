# About

ESP8266 test bench

# Usage

## Configuration

environment variables are defined in `env.conf`

```
# use provided conf example
cp ./env.conf.example ./env.conf
```

overview of the current environment vars:

```
[network]
# SSID of the network you want the device to connect to
ssid=yourssid
# WIFI password
password=networkpass
# hostname of the device when it connects to your LAN
# so you can easily do e.g. curl http://devicename.lan/
hostname=devicename

[serial]
# baudrate for serial connections
baud=115200

[eeprom]
# max eeprom size
size=512

[ntp]
# utc offset for time received from ntp call
utcoffset=-18000
# ntp endpoint
pool=pool.ntp.org
```

## Build and Deploy

compiling without flashing

```
./build
```

compiling and flashing

```
./deploy
```

monitor serial

```
./monitor
```

# Notes

mode type

```
// WIFI_STA specifies station (STA) mode and is used to get the
// ESP module connected to a Wi-Fi network established by an 
// access point.
// https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html
WiFi.mode(WIFI_STA);
WiFi.hostname(hostname);
WiFi.begin(ssid, password);
```

eeprom

```
void writeEEPROMByte(char c) {
    EEPROM.write(addr, c);
    addr = addr + 1;
    if (addr == EEPROM_SIZE) {
        addr = 0;
    }

    /*
     * apprently this writes to flash storage so it can persis across
     * boots
    if (EEPROM.commit()) {
        Serial.println("EEPROM successfully committed");
    } else {
        Serial.println("ERROR! EEPROM commit failed");
    }
    */

    // delay not needed
    // https://forum.arduino.cc/t/are-delay-needed-between-eeprom-write-put-commands/1085191
    // delay(100);
}
```
