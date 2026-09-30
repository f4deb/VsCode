#ifndef EEPROM_TOOLS_H
#define EEPROM_TOOLS_H

#include "driver/i2c_master.h"

// Interface
void eepromInit(void);
void writeEeprom(uint8_t value[], uint32_t addr, uint8_t length);
void readEepromAll(void);
void readEepromBloc(void);
void readEepromByte(void);

// Local
unsigned char* getReadBuffer(void);
unsigned char* getWriteBuffer(void);
void setBlockAddr(uint32_t addr);
void setBlockSize(uint16_t size);


#endif