#include <stdio.h>
#include <string.h>
#include "errorStoreInterface.h"
#include "errorStoreInterfaceDescriptor.h"

#include "sdkconfig.h"

#include "esp_event.h"
#include "esp_log.h"

#include "../charUtils/include/charUtils.h"
#include "../uartUtils/include/uartUtils.h"
#include "../errorCmos/include/errorCmos.h"

#include "../interface/include/interface.h"
#include "../interface/include/interfaceDescriptor.h"

#include "../uartCommand/include/uartCommand.h"
#include "../../../../esp-idf/components/esp_driver_uart/include/driver/uart.h"

#define TAG "CPU Led Interface "


uint8_t helCpuLedIndex = 0;

void errorStoreInterface(char rxBuffer[50]){
    char str[ERROR_STORE_INTERFACE_COMMAND_SIZE];
    char status[100];

    uint8_t value8 = 0;
    uint32_t value32 = 0;

    uint8_t indexLed = 0;

    if (ERROR_STORE_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", rxBuffer);
    stringToString(str,rxBuffer, ERROR_STORE_INTERFACE_COMMAND_SIZE);
    if (ERROR_STORE_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", str);
    rxBuffer++;        
   
    if ((strcmp(READ_ALL_ERROR_HEADER,str)) == 0) {       
        uartDataBackLF(status);
    }

    else if ((strcmp(WRITE_ERROR_HEADER,str)) == 0) {
        
        // Lecture Index led
        indexLed = readHex(stringToString(str,rxBuffer,2));
        rxBuffer++;        
        rxBuffer++;     

        if ( value32 < 100 ) value32 = 100;                
        if ( value32 > 10000 ) value32 = 10000;
        
        uartDataBackLF(status);
    }
    else if ((strcmp(CLEAR_ERROR_HEADER,str)) == 0) {

 
       
        uartDataBackLF(status);
    }

    
    else if ((strcmp(HELP_ERROR_STORE_HEADER,str)) == 0) {
        // Lecture 0 paramètre

        // traitement      
        errorStoreInterfaceDescriptor();
    }
    else {
        ESP_LOGE(TAG, "Bad command");
        //ERR_COMMAND_INVALID
    }
}