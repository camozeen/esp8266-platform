#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "log.h"
#include "server.h"
#include "ntp.h"
#include "route/home.h"
#include "service/eeprom.h"

const int led = 13;
// int addr = 0;

void printEnv() {
    Serial.println(NETWORK_SSID);
    server.send(200, "text/plain", "ok");
}

void getTime() {
    timeClient.update();
    Serial.print(timeClient.getEpochTime());
    server.send(200, "text/plain", "ok");
}

void route_write_eeprom() {
    if (server.args() < 1 && server.argName(0) != "data") {
        server.send(200, "text/plain", "wrote no data");
    }
    else {
        Serial.println("handling EEPROM write request");
        int buff_size = server.arg(0).length() + 1;
        char buff[buff_size];
        // TODO: size checks
        server.arg(0).toCharArray(buff, buff_size);
        write_eeprom(buff, buff_size);
        server.send(200, "text/plain", "OK");
    }
}

void route_read_eeprom() {
    char buff[512];
    read_eeprom(buff);
    server.send(200, "text/plain", buff);
}

void route_log_eeprom() {
    int start_addr = 0;
    for (int i=0; i < 10; i++){
        // read a byte from the current address of the EEPROM
        byte value = EEPROM.read(start_addr);

        Serial.print(start_addr);
        Serial.print("\t");
        Serial.print(value, DEC);
        Serial.println();

        // advance to the next address of the EEPROM
        start_addr = start_addr + 1;

        // there are only 512 bytes of EEPROM, from 0 to 511, so if we're
        // on address 512, wrap around to address 0
        if (start_addr == EEPROM_SIZE) { start_addr = 0; }

        // delay(500);
    }
    server.send(200, "text/plain", "OK");
}

void handleNotFound(){
    digitalWrite(led, 1);
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET)?"GET":"POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    for (uint8_t i=0; i<server.args(); i++){
        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    server.send(404, "text/plain", message);
    digitalWrite(led, 0);
}

void setup(void) {
    Serial.begin(SERIAL_BAUD);

    EEPROM.begin(EEPROM_SIZE);
    log_eeprom_init(EEPROM_SIZE);

    timeClient.begin();
    log_ntp_init();

    pinMode(led, OUTPUT);
    digitalWrite(led, 0);

    WiFi.mode(WIFI_STA);
    WiFi.hostname(NETWORK_HOSTNAME);
    WiFi.begin(NETWORK_SSID, NETWORK_PASSWORD);

    log_station_conn_attempt();
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
    log_station_conn_info(NETWORK_SSID, WiFi.localIP());

    if (MDNS.begin("esp8266")) {
        log_mdns_status();
    }

    server.on("/", route_home);
    server.on("/env", printEnv);
    server.on("/time", getTime);
    server.on("/eeprom/write", route_write_eeprom);
    server.on("/eeprom/read", route_read_eeprom);
    server.on("/eeprom/log", route_log_eeprom);

    server.on("/inline", [](){
        server.send(200, "text/plain", "this works as well");
    });

    server.onNotFound(handleNotFound);

    server.begin();
    log_http_server_status();
}

void loop(void){
    server.handleClient();
}
