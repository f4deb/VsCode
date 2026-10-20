#ifndef CPU_LED_INTERFACE_DESCRIPTOR_H
#define CPU_LED_INTERFACE_DESCRIPTOR_H

#include <stdint.h>

#include "../../interface/include/interfaceDescriptor.h"

#define CPU_LED_INTERFACE_DESCRIPTOR_DEBUG 0

#define CPU_LED_INTERFACE_DESCRIPTOR "Interface de Commande des leds"


InterfaceDescriptor getLedInterfaceDescriptor(void);

void initLedInterfaceDesriptor();

void cpuLedInterfaceDescriptor(void);

#endif