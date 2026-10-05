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

#define TAG "Error Store Interface "

// Lire les erreurs enregistrées
error_log_entry_t logs[MAX_ERROR_LOGS];
size_t count = 0;

unsigned int  errorCode;

uint8_t helpErrorStoreIndex = 0;


void readAllError(void){
    char status[50];
    char str[50];

    if (error_store_read_all(logs, &count) == ESP_OK) {
        ESP_LOGI(TAG, "Nombre d'erreurs en mémoire : %zu", count);
        for (size_t i = 0; i < count; i++) {
            errorCode = (unsigned int)(logs[i].err_code & 0xFFFFF);

            ESP_LOGI(TAG, "[%lu ms] Code: 0x%x | Msg: %s",
            logs[i].timestamp, errorCode, logs[i].message);


            //sprintf(str,"%2x ", errorCode);       
            sprintf(str, "%x ", errorCode);       
            uartDataBackLF(str);
        }
    }  
}

void errorStoreInit(void){
        
    ESP_ERROR_CHECK(error_store_init());

    //error_store_write(ESP_FAIL, "12345");
    
    readAllError();   
}


void errorStoreInterface(char rxBuffer[50]){
    char str[50];
    char status[50];

    uint8_t value8 = 0;
    uint32_t value32 = 0;

    uint8_t indexLed = 0;

    if (ERROR_STORE_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", rxBuffer);
    stringToString(str,rxBuffer, ERROR_STORE_INTERFACE_COMMAND_SIZE);
    if (ERROR_STORE_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", str);
    rxBuffer++;        
   
    if ((strcmp(READ_ALL_ERROR_HEADER,str)) == 0) {       


    
// Lecture des erreurs

    if (ERROR_STORE_INTERFACE_DEBUG) ESP_LOGI("STACK", "High water mark: %u octets libres", (unsigned)uxTaskGetStackHighWaterMark(NULL));
    readAllError();   
    if (ERROR_STORE_INTERFACE_DEBUG) ESP_LOGI("STACK", "High water mark: %u octets libres", (unsigned)uxTaskGetStackHighWaterMark(NULL));

        //uartDataBackLF(status);
    }

    else if ((strcmp(WRITE_ERROR_HEADER,str)) == 0) {
        error_store_write(0x12345678, "ABCDEFGH");

        uartDataBackLF(status);
    }
    else if ((strcmp(CLEAR_ERROR_HEADER,str)) == 0) {
        error_store_clear();
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