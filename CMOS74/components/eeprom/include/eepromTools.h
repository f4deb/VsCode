#ifndef EEPROM_TOOLS_H
#define EEPROM_TOOLS_H

#include "driver/i2c_master.h"

void eepromInit(void);
void writeEeprom(uint8_t value[], uint32_t addr, uint8_t length);
void readEeprom(void);

unsigned char* getReadBuffer(void);
unsigned char* getWriteBuffer(void);
void setBlockAddr(uint32_t addr);
void setBlockSize(uint8_t size);

#endif