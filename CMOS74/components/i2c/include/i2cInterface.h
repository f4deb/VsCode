#ifndef I2C_INTERFACE_H
#define I2C_INTERFACE_H

#include "../../charUtils/include/charUtils.h"

#define I2C_INTERFACE_DEBUG 0

#define I2C_INTERFACE_HEADER_NAME "I2C"

#define I2C_INTERFACE_HEADER "i2"

#define I2C_INTERFACE_HEADER_SIZE 2
#define I2C_INTERFACE_COMMAND_SIZE 1

#define I2C_DETECT_HEADER "c"
#define I2C_HELP_HEADER "h"
#define I2C_WRITE_DATA "W"
#define I2C_READ_DATA "R"

void i2cInterface(char rxBuffer[50]);

#endif