#include <stdio.h>
#include <string.h>
#include "eepromTools.h"
#include "eepromInterface.h"
#include "eepromInterfaceDescriptor.h"

#include "sdkconfig.h"

#include "esp_event.h"
#include "esp_log.h"

#include "../charUtils/include/charUtils.h"
#include "../driverCmos/eeprom/include/i2cEeprom.h"
#include "../i2c/include/i2cTools.h"
#include "../uartUtils/include/uartUtils.h"

#include "../interface/include/interface.h"
#include "../interface/include/interfaceDescriptor.h"

#include "../uartCommand/include/uartCommand.h"

#include "../../../../esp-idf/components/esp_driver_uart/include/driver/uart.h"

#define TAG "EEPROM Interface"

void eepromInterface(char rxBuffer[50]){

    char str[EEPROM_INTERFACE_COMMAND_SIZE];
    char status[20];
    if (EEPROM_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", rxBuffer);

    stringToString(str,rxBuffer, EEPROM_INTERFACE_COMMAND_SIZE);

    if (EEPROM_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", str);
 
    rxBuffer++;        


    if ((strcmp(EEPROM_WRITE_HEADER,str)) == 0) {
        uint8_t buf[16];


        buf[0] = readHex(stringToString(str,rxBuffer,2));
        rxBuffer++;        
        rxBuffer++;       
        writeEeprom(buf, 0,1);
        
        buf[0] = readHex(stringToString(str,rxBuffer,2));
        rxBuffer++;        
        rxBuffer++;       
        writeEeprom(buf, 1,1);



        if (EEPROM_INTERFACE_DEBUG) ESP_LOGE(TAG, "%s ", str);
    }
    else if ((strcmp(EEPROM_READ_HEADER,str)) == 0) {
        // traitement      
        readEeprom();
    }
    else if ((strcmp(EEPROM_SET_ADDRESSE_HEADER,str)) == 0) {
        // Lecture 0 paramètre

        // traitement      
        setBlockAddr(readHex(stringToString(str,rxBuffer,4)));
        rxBuffer++;        
        rxBuffer++;         
        rxBuffer++;        
        rxBuffer++; 
    }    
    else if ((strcmp(EEPROM_HELP_HEADER,str)) == 0) {
        // Lecture 0 paramètre

        // traitement      
        eepromInterfaceDescriptor();
    }
    else {
        ESP_LOGE(TAG, "Bad command");
    }
}