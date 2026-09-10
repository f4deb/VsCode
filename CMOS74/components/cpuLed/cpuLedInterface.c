#include <stdio.h>
#include <string.h>
#include "cpuLedInterface.h"
#include "cpuLedInterfaceDescriptor.h"

#include "sdkconfig.h"

#include "esp_event.h"
#include "esp_log.h"

#include "../charUtils/include/charUtils.h"
#include "../uartUtils/include/uartUtils.h"
#include "../errorCmos/include/errorCmos.h"

#include "../cpuLed/include/cpuLed.h"
#include "../interface/include/interface.h"
#include "../interface/include/interfaceDescriptor.h"

#include "../uartCommand/include/uartCommand.h"
#include "../../../../esp-idf/components/esp_driver_uart/include/driver/uart.h"

#define TAG "CPU Led Interface "


uint8_t helCpuLedIndex = 0;

void cpuLedInterface(char rxBuffer[50]){
    char str[CPU_LED_INTERFACE_COMMAND_SIZE];
    char status[100];

    uint8_t value8 = 0;
    uint32_t value32 = 0;

    uint8_t indexLed = 0;

    if (CPU_LED_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", rxBuffer);
    stringToString(str,rxBuffer, CPU_LED_INTERFACE_COMMAND_SIZE);
    if (CPU_LED_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", str);
    rxBuffer++;        
   
    if ((strcmp(SET_RATIO_BLINK_HEADER,str)) == 0) {
        // Lecture Index led
        indexLed = readHex(stringToString(str,rxBuffer,2));
        rxBuffer++;        
        rxBuffer++;     

        value8 = readSeparator(stringToString(str,rxBuffer,1));
        rxBuffer++;    

        value8 = readDec(stringToString(str,rxBuffer,3));
        rxBuffer++;
        rxBuffer++;
        rxBuffer++;

        // traitement
        led_config_t *config = get_my_leds(indexLed);
        config->ratio_ms = value8;
        
        uartDataBackLF(status);

    }

    else if ((strcmp(SET_TIME_BLINK_HEADER,str)) == 0) {
        
        // Lecture Index led
        indexLed = readHex(stringToString(str,rxBuffer,2));
        rxBuffer++;        
        rxBuffer++;     

        value8 = readSeparator(stringToString(str,rxBuffer,1));
        rxBuffer++;    

        value32 = readDec(stringToString(str,rxBuffer,4));
        rxBuffer++;
        rxBuffer++;
        rxBuffer++;
        rxBuffer++;

        if ( value32 < 100 ) value32 = 100;                
        if ( value32 > 10000 ) value32 = 10000;
        // traitement
        led_config_t *config = get_my_leds(indexLed);
        config->delay_ms = value32;
        
        uartDataBackLF(status);
    }
    else if ((strcmp(SET_CPU_LED_HEADER,str)) == 0) {

 // Lecture Index led
        indexLed = readHex(stringToString(str,rxBuffer,2));
        rxBuffer++;        
        rxBuffer++;     

        value8 = readSeparator(stringToString(str,rxBuffer,1));
        rxBuffer++;    

        value8 = readHex(stringToString(str,rxBuffer,2));
        rxBuffer++;
        rxBuffer++;

        if (value8 == 0) { 
            value32 = 0 ;
        }
        else if (value8 == 1 ){
            value32 = 100;
        } 
        // traitement
        led_config_t *config = get_my_leds(indexLed);
        config->ratio_ms = value32;
       
        uartDataBackLF(status);
    }

    else if ((strcmp(GET_CPU_LED_NAME_HEADER,str)) == 0) {
        char *name = "toto";    
        // Lecture Index led
        indexLed = readHex(stringToString(str,rxBuffer,2));
        if (( indexLed  < 0 ) || ( indexLed  > INDEXMAX )){
            name = "Format command error ERROR 0x1111";
            ESP_LOGE(TAG, "%s",name);
            stringToString(status, name,strlen(name));       
            uartDataBackCR(status);
            return;
        }                
        else {               
                // traitement
            led_config_t *config = get_my_leds(indexLed);
            name = config->led_name;
        }
        rxBuffer++;
        rxBuffer++;
        
        ESP_LOGI(TAG, "%s",name);
        stringToString(status, name,strlen(name));       
        uartDataBackCR(status);
    }

    else if ((strcmp(GET_CPU_LED_HEADER,str)) == 0) {
        char *name = "toto";    
        // Lecture Index led
        indexLed = readHex(stringToString(str,rxBuffer,2));
        if (( indexLed  < 0 ) || ( indexLed  > INDEXMAX )){
            name = "Format command error ERROR 0x1111";
            ESP_LOGE(TAG, "%s",name);
            stringToString(status, name,strlen(name));       
            uartDataBackCR(status);
            return;
        }                

        led_config_t *config = get_my_leds(indexLed);

        rxBuffer++;
        rxBuffer++;

        if (config->status == 0) name = "1";
        else if (config->status == 1) name = "0";
        else  name = "read le error";

        stringToString(status, name,strlen(name));       
        uartDataBackCR(status);
    }
    else if ((strcmp(HELP_CPU_LED_HEADER,str)) == 0) {
        // Lecture 0 paramètre

        // traitement      
        cpuLedInterfaceDescriptor();

        //error_print_last_log();
    }
    else {
        ESP_LOGE(TAG, "Bad command");
        //ERR_COMMAND_INVALID
    }
}