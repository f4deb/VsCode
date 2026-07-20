#include <stdio.h>
#include <string.h>
#include "cpuLedInterface.h"
#include "cpuLedInterfaceDescriptor.h"

#include "sdkconfig.h"

#include "esp_event.h"
#include "esp_log.h"

#include "../charUtils/include/charUtils.h"
#include "../uartUtils/include/uartUtils.h"

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

    uint8_t ledNumber = 0;
    uint8_t ledColor = 0;
    uint8_t s_led_state = 0;
    uint8_t value8 = 0;
    uint32_t value32 = 0;

    uint8_t indexLed = 0;

    if (CPU_LED_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", rxBuffer);
    stringToString(str,rxBuffer, CPU_LED_INTERFACE_COMMAND_SIZE);
    if (CPU_LED_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", str);
    rxBuffer++;        
 
    if ((strcmp(SET_RATIO_BLINK_HEADER,str)) == 0) {
        // Lecture 3 paramètres
        ledNumber = readHex(stringToString(str,rxBuffer,2));
        rxBuffer++;        
        rxBuffer++;        

        ledColor = readHex(stringToString(str,rxBuffer,2));
        rxBuffer++;        
        rxBuffer++;        

        value8 = readDec(stringToString(str,rxBuffer,2));
      
        // traitement
        if (ledNumber == LED1_RED_GPIO){
            //setRatioBlink(getLed1(),ledColor,value8);
        }
        else if (ledNumber == LED1_GREEN_GPIO){
            //setRatioBlink(getLed2(),ledColor,value8);
        }
        else {
            if (CPU_LED_INTERFACE_DEBUG) ESP_LOGE(TAG, "Invalid Led number");
            //s_led_state= 0x99;
        }        

        uartDataBackLF(status);

    }



 else if ((strcmp(GET_CPU_LED_NAME_HEADER,str)) == 0) {
        char *name;
        // Lecture Index led

        

        value8 = readSeparator(stringToString(str,rxBuffer,1));
        rxBuffer++; 


        if ( value8 < 0 ) value8 = 0;                
        if ( value8 > 3 ) value8 = 3;

        indexLed = readHex(stringToString(str,rxBuffer,2));
        rxBuffer++;        
        rxBuffer++;     

        // traitement
        led_config_t *config = get_my_leds(indexLed);
        name = config->led_name;
        if (CPU_LED_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s",name);

        stringToString(status, name,strlen(name));
        
        uartDataBackCR(status);
    }






    else if ((strcmp(SET_TIME_BLINK_HEADER,str)) == 0) {
        
        // Lecture Index led

        value8 = readSeparator(stringToString(str,rxBuffer,1));
        rxBuffer++; 

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
        if (ledNumber == LED1_GREEN_GPIO){
            //setRatioBlink(getLed1(),ledColor,value8);
        }
        else if (ledNumber == LED1_GREEN_GPIO){
            //setRatioBlink(getLed2(),ledColor,value8);
        }
        else {
            if (CPU_LED_INTERFACE_DEBUG) ESP_LOGE(TAG, "Invalid Led number");
            s_led_state= 0x99;
        }        

        uartDataBackLF(status);
    }
    else if ((strcmp(GET_CPU_LED_HEADER,str)) == 0) {
        // Lecture 2 paramètres
        ledNumber = readHex(stringToString(str,rxBuffer,2));
        ledColor = readHex(stringToString(str,rxBuffer,2));

        // traitement
        if (ledNumber == LED1_GREEN_GPIO){
            //s_led_state= getCpuLed(getLed1(),ledColor);
        }
        else if (ledNumber == LED1_GREEN_GPIO){
            //s_led_state= getCpuLed(getLed2(),ledColor);
        }
        else {
            if (CPU_LED_INTERFACE_DEBUG) ESP_LOGE(TAG, "Invalid Led number");
            //s_led_state= 0x99;
        }        
        if (CPU_LED_INTERFACE_DEBUG) ESP_LOGE(TAG, "LED Status : %s", s_led_state == true ? "ON" : "OFF");
        sprintf (status,"%02x", s_led_state );        
            
        uartDataBackLF(status);
    }
    else if ((strcmp(HELP_CPU_LED_HEADER,str)) == 0) {
        // Lecture 0 paramètre

        // traitement      
        cpuLedInterfaceDescriptor();
    }
    else {
        ESP_LOGE(TAG, "Bad command");
    }
}