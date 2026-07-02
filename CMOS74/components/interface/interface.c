#include <stdio.h>
#include <string.h>
#include "interface.h"
#include "interfaceDescriptor.h"


#include "sdkconfig.h"

#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_log.h"

#include "../uartCommand/include/uartCommand.h"
#include "../cpuLed/include/cpuLed.h"
#include "../cpuLed/include/cpuLedInterface.h"
//#include "../clock/include/clockInterface.h"
#include "../eeprom/include/eepromInterface.h"
//#include "../8IoButtonBoard/include/8IoButtonBoardInterface.h"
//#include "../Oled/include/OledInterface.h"
#include "../i2c/include/i2cInterface.h"
//#include "../sensor/include/sensorInterface.h"

#define TAG "Interface"

const char *interfaceHeader = "jk+";

const char* interface_err_to_name(esp_err_t err) {
    switch (err) {
        case ESP_ERR_NO_SEPARATOR:     return "ESP_ERR_SEPARATOR_MISSED";
//        case ESP_ERR_MOTEUR_SURCHAUFFE: return "ESP_ERR_MOTEUR_SURCHAUFFE";
        default:                        return esp_err_to_name(err); // Erreurs standards ESP-IDF
    }
}


void interface_task(void *arg){
    char rxBuffer[BUF_SIZE];
    char str[INTERFACE_HEADER_SIZE];

    for(;;) {

        if (INTERFACE_DEBUG) ESP_LOGI(TAG, "debug interface");

        if (xQueueReceive(getQueueUart2(), &(rxBuffer), (TickType_t)5)) {
            if (INTERFACE_DEBUG) ESP_LOGI(TAG, "%s ", rxBuffer);
            stringToString(str,rxBuffer,strlen(interfaceHeader));
            if (INTERFACE_DEBUG) ESP_LOGI(TAG, "%s ", str);
            if ((strcmp(interfaceHeader,str)) == 0) {

                stringToString(str,rxBuffer+3,2);
                if (INTERFACE_DEBUG) ESP_LOGI(TAG, "%s ", str);


                // CPU Led Interface
                if ((strcmp(CPU_LED_INTERFACE_HEADER,str)) == 0) {
                    cpuLedInterface(rxBuffer+(5));
                }
                // Clock
                /* else if ((strcmp(CLOCK_INTERFACE_HEADER,str)) == 0) {
                    //clockInterface(rxBuffer+5);
                }
                // 8IoButtonBoard
                else if ((strcmp(IO_BUTTON_BOARD_INTERFACE_HEADER,str)) == 0) {
                    //ioButtonBoardInterface(rxBuffer+5);
                }     */
                // I2C
                else if ((strcmp(I2C_INTERFACE_HEADER,str)) == 0) {
                    i2cInterface(rxBuffer+5);
                }      
                // EEPROM
                else if ((strcmp(EEPROM_INTERFACE_HEADER,str)) == 0) {
                    eepromInterface(rxBuffer+5);
                }       
                /*        
                // Oled
                else if ((strcmp(OLED_INTERFACE_HEADER,str)) == 0) {
                    //oledInterface(rxBuffer+5);
                }            
                // SENSOR
                else if ((strcmp(SENSOR_INTERFACE_HEADER,str)) == 0) {
                    //sensorInterface(rxBuffer+5);
                }   */            
            }
            else {
                //printHelp();
            }
            
        }   
    //vTaskDelay(pdMS_TO_TICKS(1));
    }
}