#ifndef ERROR_STORE_INTERFACE
#define ERROR_STORE_INTERFACE

#include "../../charUtils/include/charUtils.h"
#include "../../errorStore//include/errorStore.h"

#define ERROR_STORE_INTERFACE_DEBUG 1

#define ERROR_STORE_INTERFACE_HEADER_NAME "ERROR STORE"

#define ERROR_STORE_INTERFACE_HEADER "es"

#define ERROR_STORE_INTERFACE_HEADER_SIZE 2
#define ERROR_STORE_INTERFACE_COMMAND_SIZE 1

#define READ_ALL_ERROR_HEADER "R"
#define WRITE_ERROR_HEADER "w"
#define CLEAR_ERROR_HEADER "C"
#define HELP_ERROR_STORE_HEADER "h"

void errorStoreInit(void);


void errorStoreInterface(char rxBuffer[50]);

#endif