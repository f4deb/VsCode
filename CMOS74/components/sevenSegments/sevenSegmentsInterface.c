#include <stdio.h>
#include <string.h>
#include "sevenSegmentsInterface.h"
#include "sevenSegmentsInterfaceDescriptor.h"

#include "sdkconfig.h"

#include "esp_event.h"
#include "esp_log.h"

#include "../charUtils/include/charUtils.h"
#include "../uartUtils/include/uartUtils.h"

#include "../sevenSegments/include/sevenSegments.h"
#include "../interface/include/interface.h"
#include "../interface/include/interfaceDescriptor.h"

#include "../uartCommand/include/uartCommand.h"
#include "../../../../esp-idf/components/esp_driver_uart/include/driver/uart.h"

#define TAG "CPU Led Interface "


uint8_t helSevenSegmentsdIndex = 0;

void sevenSegmentsInterface(char rxBuffer[50]){
    char str[SEVEN_SEGMENTS_INTERFACE_COMMAND_SIZE];
    char status[100];

    uint8_t ledNumber = 0;
    uint8_t ledColor = 0;
    uint8_t s_led_state = 0;
    uint8_t value8 = 0;
    uint32_t value32 = 0;

    if (SEVEN_SEGMENTS_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", rxBuffer);
    stringToString(str,rxBuffer, SEVEN_SEGMENTS_INTERFACE_COMMAND_SIZE);
    if (SEVEN_SEGMENTS_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", str);
    rxBuffer++;        
   
    if ((strcmp(WRITE_ONE_SEVEN_SEGMENTS_HEADER,str)) == 0) {
        // Lecture 3 paramètres
        ledNumber = readHex(stringToString(str,rxBuffer,2));
        rxBuffer++;        
        rxBuffer++;        

        ledColor = readHex(stringToString(str,rxBuffer,2));
        rxBuffer++;        
        rxBuffer++;        

        value8 = readDec(stringToString(str,rxBuffer,2));
      
        // traitement
        

        uartDataBackLF(status);

    }
    else if ((strcmp(WRITE_TWO_SEVEN_SEGMENTS_HEADER,str)) == 0) {
        // Lecture 3 paramètres
        ledNumber = readHex(stringToString(str,rxBuffer,2));
        rxBuffer++;        
        rxBuffer++;        

        ledColor = readHex(stringToString(str,rxBuffer,2));
        rxBuffer++;        
        rxBuffer++;        

        value32 = readDec(stringToString(str,rxBuffer,4));
      
        // traitement
       

        uartDataBackLF(status);
    }
    else if ((strcmp(WRITE_THREE_SEVEN_SEGMENTS_HEADER,str)) == 0) {

 // Lecture 3 paramètres
        ledNumber = readHex(stringToString(str,rxBuffer,2));
        rxBuffer++;        
        rxBuffer++;       
        ledColor = readHex(stringToString(str,rxBuffer,2));
        rxBuffer++;        
        rxBuffer++;        

        value8 = readDec(stringToString(str,rxBuffer,2));

        if (value8 > 0){
            value8 = 99;
        } 
      
        // traitement
       

        uartDataBackLF(status);
    }
    else if ((strcmp(WRITE_FOR_SEVEN_SEGMENTS_HEADER,str)) == 0) {
        // Lecture 2 paramètres
        ledNumber = readHex(stringToString(str,rxBuffer,2));
        ledColor = readHex(stringToString(str,rxBuffer,2));

        // traitement
        
            
        uartDataBackLF(status);
    }
    else if ((strcmp(SEVEN_SEGMENTS_HELP_HEADER,str)) == 0) {
        // Lecture 0 paramètre

        // traitement      
        sevenSegmentsInterfaceDescriptor();
    }
    else {
        ESP_LOGE(TAG, "Bad command");
    }
}