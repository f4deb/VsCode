#ifndef EEPROM_INTERFACE_DESCRIPTOR_H
#define EEPROM_INTERFACE_DESCRIPTOR_H

#include <stdint.h>
#include "../../interface/include/interfaceDescriptor.h"

#define EEPROM_INTERFACE_DESCRIPTOR_DEBUG 0

#define EEPROM_INTERFACE_DESCRIPTOR "Interface de gestion de l'EEPROM"

InterfaceDescriptor* getEepromInterfaceDescriptor(void);
void initEepromInterfaceDescriptor(void);
void printEepromInterfaceDescriptor(void);

#endif