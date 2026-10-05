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

void errorStoreInterfaceDescriptor(void){  
    printDeviceLine();
    printHelpTitle(INTERFACE_HEADER, ERROR_STORE_INTERFACE_HEADER,"     ", ERROR_STORE_INTERFACE_HEADER_NAME);
    printDeviceLine();
    printTableLine("help : h","input : 0","Ouput : 0 "," ");
    printTableBlank();
    printTableLine("Name  : w","input : 4","Ouput :  0"," ");
    printTableLine("Code Error ","        HEX4"," "," ");
    printTableBlank();
    printTableLine("Name  : R","input : 0","Ouput :  4"," ");
    printTableLine("List "," ","TEXT "," ");
    printTableBlank();
    printTableLine("Clear : C","input : 0","Ouput : 0 "," "); 
    printDeviceLine();
}