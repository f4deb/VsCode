#ifndef EEPROM_INTERFACE_H
#define EEPROM_INTERFACE_H

#include "../../charUtils/include/charUtils.h"

#define EEPROM_INTERFACE_DEBUG 0

#define EEPROM_INTERFACE_HEADER_NAME "EEPROM"

#define EEPROM_INTERFACE_HEADER "ee"

#define EEPROM_INTERFACE_HEADER_SIZE 2
#define EEPROM_INTERFACE_COMMAND_SIZE 1

#define EEPROM_WRITE_HEADER "w"
#define EEPROM_READ_HEADER "r"
#define EEPROM_HELP_HEADER "h"

void eepromInterface(char rxBuffer[50]);

#endif