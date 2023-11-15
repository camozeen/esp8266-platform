#include <HardwareSerial.h>
#include <IPAddress.h>
#include "log.h"

void log_eeprom_init(int size) {
    Serial.println("");
    Serial.print("EEPROM INITIALIZED WITH SIZE: ");
    Serial.println(size);
}

void log_ntp_init() {
    Serial.println("TIME CLIENT INITIALIZED");
}

void log_station_conn_attempt() {
    Serial.println("ATTEMPTING CONNECTION TO AP");
}

void log_station_conn_info(const char * ssid, const IPAddress & ip) {
    Serial.println("CONNECTION TO AP ESTABLISHED");
    Serial.print("  |-> SSID: ");
    Serial.println(ssid);
    Serial.print("  |-> IP: ");
    Serial.println(ip);
}

void log_mdns_status() {
    Serial.println("MDNS RESPONDER STARTED");
}

void log_http_server_status() {
    Serial.println("HTTP SERVER STARTED");
}
