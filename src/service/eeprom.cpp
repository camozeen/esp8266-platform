#include <EEPROM.h>
#include "service/eeprom.h"

int addr = 0;

int write_eeprom(char data[], int size) {
    for (int i = 0; i < size; i++) {
        EEPROM.write(addr, data[i]);
        addr = addr + 1;
        if (addr == EEPROM_SIZE) {
            addr = 0;
        }
    }
    return 0;
}

int read_eeprom(char data[]) {
    for (int i = 0; i < addr; i++) {
        char value = EEPROM.read(i);
        data[i] = (char)value;
    }
    return 0;
}
