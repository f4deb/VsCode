#include <stdio.h>
#include <string.h>
#include "errorStoreInterface.h"
#include "errorStoreInterfaceDescriptor.h"

#include "sdkconfig.h"

#include "esp_event.h"
#include "esp_log.h"

#include "../charUtils/include/charUtils.h"
#include "../uartUtils/include/uartUtils.h"

#include "../errorStore/include/errorStore.h"
#include "../interface/include/interface.h"
#include "../interface/include/interfaceDescriptor.h"

#include "../uartCommand/include/uartCommand.h"
#include "../../../../esp-idf/components/esp_driver_uart/include/driver/uart.h"

#define TAG "Error Store Interface Descrtiptor "

static const char* errorStoreInterfaceName = ERROR_STORE_INTERFACE_HEADER_NAME; 
static const char* errorStoreInterfaceCommand = INTERFACE_HEADER ERROR_STORE_INTERFACE_HEADER; 
static const char* errorStoreInterfaceDescriptort = ERROR_STORE_INTERFACE_DESCRIPTOR; 

static InterfaceDescriptor errorStroreInterfaceDescriptor;

InterfaceDescriptor getErrorStoreInterfaceDescriptor(void){
    return errorStroreInterfaceDescriptor;
}

void initErrorStoreInterfaceDesriptor(){
    InterfaceList *list;
    uint8_t index;
    list = getInterfaceList();
    index = list->currentIndex;

    if (!errorStroreInterfaceDescriptor.isInit){
        errorStroreInterfaceDescriptor.isInit = true;
        errorStroreInterfaceDescriptor.index = index;
        errorStroreInterfaceDescriptor.name = getInterfaceName(errorStoreInterfaceName);
        errorStroreInterfaceDescriptor.command = getInterfaceCommand(errorStoreInterfaceCommand);
        errorStroreInterfaceDescriptor.description = getInterfaceDescription(errorStoreInterfaceDescriptort);    
    }

}

void errorStoreInterfaceDescriptor(void){  
    printDeviceLine();
    printHelpTitle(errorStroreInterfaceDescriptor.command,  " / ", errorStroreInterfaceDescriptor.name, errorStroreInterfaceDescriptor.description);
    printDeviceLine();
    printTableCode("help : "HELP_ERROR_STORE_HEADER,0x10000,0x20000);
    printTableBlank();
    printTableLine("Write single Error  : "WRITE_ERROR_HEADER,"input : 4","Ouput :  0"," ");
    printTableLine(" ","        HEX4"," "," ");
    printTableBlank();
    printTableLine("Print error list  : "READ_ALL_ERROR_HEADER,"input : 0","Ouput :  4"," ");
    printTableLine(" "," ","TEXT "," ");
    printTableBlank();
    printTableLine("Clear error list : "CLEAR_ERROR_HEADER,"input : 0","Ouput : 0 "," "); 
    printDeviceLine();
}