#ifndef EEPROM_TOOLS_H
#define EEPROM_TOOLS_H

#include "driver/i2c_master.h"

void  eepromInit(void);

void writeEeprom(void);

void readEeprom(void);

#endif