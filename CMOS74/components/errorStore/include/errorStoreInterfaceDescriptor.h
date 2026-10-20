#ifndef ERROR_STORE_INTERFACE_DESCRIPTOR_H
#define ERROR_STORE_INTERFACE_DESCRIPTOR_H

#include <stdint.h>
#include "../../interface/include/interfaceDescriptor.h"

#define ERROR_STORE_INTERFACE_DESCRIPTOR_DEBUG 1

#define ERROR_STORE_INTERFACE_DESCRIPTOR "Interface de gestion des erreurs"

InterfaceDescriptor getErrorStoreInterfaceDescriptor(void);

void initErrorStoreInterfaceDesriptor();

void errorStoreInterfaceDescriptor(void);

#endif