#ifndef I2C_INTERFACE_DESCRIPTOR_H
#define I2C_INTERFACE_DESCRIPTOR_H

#include <stdint.h>
#include "../../interface/include/interfaceDescriptor.h"

#define I2C_INTERFACE_DESCRIPTOR_DEBUG 0

#define I2C_INTERFACE_DESCRIPTOR "Interface I2C"

InterfaceDescriptor* getI2cInterfaceDescriptor(void);

void initI2cInterfaceDescriptor(void);

void printI2cInterfaceDescriptor(void);

#endif