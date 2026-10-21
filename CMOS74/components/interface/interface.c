#include <stdio.h>
#include <string.h>
#include "interfaceDescriptor.h"
#include "interface.h"
#include "charUtils.h"



#include "sdkconfig.h"

#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_log.h"

#include "../errorCmos/include/errorCmos.h"

#include "../uartCommand/include/uartCommand.h"
#include "../cpuLed/include/cpuLed.h"
#include "../cpuLed/include/cpuLedInterface.h"
#include "../cpuLed/include/cpuLedInterfaceDescriptor.h"
//#include "../clock/include/clockInterface.h"
#include "../eeprom/include/eepromInterface.h"
#include "../errorStore/include/errorStoreInterface.h"
#include "../errorStore/include/errorStoreInterfaceDescriptor.h"
//#include "../8IoButtonBoard/include/8IoButtonBoardInterface.h"
//#include "../Oled/include/OledInterface.h"
#include "../i2c/include/i2cInterface.h"
//#include "../sensor/include/sensorInterface.h"
#include "../uartUtils/include/uartUtils.h"

#define TAG "Interface"

const char *interfaceHeader = "jk+";

const char* interface_err_to_name(esp_err_t err) {
    switch (err) {
        case ESP_ERR_NO_SEPARATOR:     return "ESP_ERR_SEPARATOR_MISSED";
//        case ESP_ERR_MOTEUR_SURCHAUFFE: return "ESP_ERR_MOTEUR_SURCHAUFFE";
        default:                        return esp_err_to_name(err); // Erreurs standards ESP-IDF
    }
}

const char* interfaceName = "interface test Command"; 
const char* interfaceCommand = "jk+test"; 
const char* interfaceDescriptort= "test descriptor"; 

static InterfaceDescriptor interfaceDescriptor;
static InterfaceList interfaceList;


InterfaceList* getInterfaceList(void){
    return &interfaceList;
}

InterfaceDescriptor getInterfaceDescriptor(void){
    return interfaceDescriptor;
}

char* getInterfaceName(char* name){
    return name;
}

char* getInterfaceDescription(char* descrptor){
    return descrptor;
}

char* getInterfaceCommand(char* command){
    return command;
}

void initInterfaceDscriptor(void){
    interfaceDescriptor.index = 0;
    interfaceDescriptor.name = getInterfaceName(interfaceName);
    interfaceDescriptor.command = getInterfaceCommand(interfaceCommand);
    interfaceDescriptor.description = getInterfaceDescription(interfaceDescriptort);
}

void createInterfaceDescriptor(){
    
    initInterfaceDscriptor();

}

void createInterfaceDescriptorToList(InterfaceDescriptor* descriptor){

    if (!interfaceList.isInit){
        interfaceList.isInit = true;
        interfaceList.currentIndex = 0;
        interfaceList.indexMax = INTERFACE_DESCRIPTOR_INDEX_MAX;
        interfaceList.map[interfaceList.currentIndex] = getInterfaceDescriptor();
        interfaceList.currentIndex++;
        interfaceList.map[interfaceList.currentIndex] = getLedInterfaceDescriptor();
        interfaceList.currentIndex++;
        interfaceList.map[interfaceList.currentIndex] = getErrorStoreInterfaceDescriptor();
        interfaceList.currentIndex++;
    }    
}

void addInterfaceDescriptorToList(){

}

void printInterfaceDescriptor(){

    InterfaceDescriptor test;
    test = interfaceList.map[1];

    ESP_LOGI(TAG, "%s",test.name);
    ESP_LOGI(TAG, "%s",test.command);  
    
    ESP_LOGI(TAG, "%s",test.description);

        test = interfaceList.map[0];

    ESP_LOGI(TAG, "%s",test.name);
    ESP_LOGI(TAG, "%s",test.command);  
    ESP_LOGI(TAG, "%s",test.description);
}




void interface_task(void *arg){

    char rxBuffer[BUF_SIZE];
    char str[INTERFACE_HEADER_SIZE];
    char status[50] ;
    char *name="tt";

    createInterfaceDescriptor();
    createInterfaceDescriptorToList(&interfaceDescriptor);

    for(;;) {
        if (xQueueReceive(getQueueUart2(), &(rxBuffer), (TickType_t)5)) {
            if (INTERFACE_DEBUG) ESP_LOGI(TAG, "%s ", rxBuffer);
            stringToString(str,rxBuffer,strlen(interfaceHeader));
            if (INTERFACE_DEBUG) ESP_LOGI(TAG, "%s ", str);
            if ((strcmp(interfaceHeader,str)) == 0) {
                stringToString(str,rxBuffer+3,2);
                if (INTERFACE_DEBUG) ESP_LOGI(TAG, "%s ", str);

                // CPU Led Interface
                if ((strcmp(CPU_LED_INTERFACE_HEADER,str)) == 0) {
                    //initLedInterfaceDesriptor();

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
                // ERROR STORE
                else if ((strcmp(ERROR_STORE_INTERFACE_HEADER,str)) == 0) {
                    //printInterfaceDescriptor();
                    //initErrorStoreInterfaceDesriptor();

                    errorStoreInterface(rxBuffer+5);

                    
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
                else {
                    //stringToString(status, name,strlen(name));       
                    
                    //ESP_LOGE(TAG, "%s",status);
                    //uartDataBackCR(status); 
                }            
            }   
        }
        if (INTERFACE_DEBUG) {
            UBaseType_t uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
            ESP_LOGI("STACK", "Stack minimum restant : %u octets", (unsigned int)uxHighWaterMark);
        }   
    }   
}