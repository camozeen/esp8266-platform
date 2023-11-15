#ifndef __LOG_H
#define __LOG_H

#include <IPAddress.h>

void log_eeprom_init(int size);
void log_ntp_init();
void log_station_conn_attempt();
void log_station_conn_info(const char * ssid, const IPAddress & ip);
void log_mdns_status();
void log_http_server_status();

#endif // __LOG_H
