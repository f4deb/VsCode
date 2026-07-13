#ifndef EEPROM_INTERFACE_H
#define EEPROM_INTERFACE_H

#include "esp_err.h"

#include "../../charUtils/include/charUtils.h"

#define EEPROM_INTERFACE_DEBUG 1

#define EEPROM_INTERFACE_HEADER_NAME "EEPROM"

#define EEPROM_INTERFACE_HEADER "ee"

#define EEPROM_INTERFACE_HEADER_SIZE 2
#define EEPROM_INTERFACE_COMMAND_SIZE 1

#define EEPROM_BLOCK_WRITE_HEADER "W"
#define EEPROM_BYTE_WRITE_HEADER "w"
#define EEPROM_SET_ADDRESSE_HEADER "a"
#define EEPROM_READ_HEADER "r"
#define EEPROM_HELP_HEADER "h"

int eepromInterface(char rxBuffer[50]);

#endif