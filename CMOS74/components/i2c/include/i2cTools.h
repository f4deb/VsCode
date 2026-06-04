#ifndef I2C_TOOLS_H
#define I2C_TOOLS_H

#include "driver/i2c_master.h"

uint8_t I2cBusInit(void);

void i2cDetect(void);

i2c_master_bus_handle_t getI2cBus (void);

#endif