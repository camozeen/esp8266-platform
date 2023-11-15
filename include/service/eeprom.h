#ifndef __SERVICE_EEPROM
#define __SERVICE_EEPROM

extern int addr;

int write_eeprom(char data[], int size);
int read_eeprom(char data[]);


#endif // __SERVICE_EEPROM
