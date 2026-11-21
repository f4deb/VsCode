#include <stdio.h>
#include <string.h>
#include "i2cInterface.h"
#include "i2cInterfaceDescriptor.h"

#include "sdkconfig.h"

#include "esp_event.h"
#include "esp_log.h"

#include "../charUtils/include/charUtils.h"
#include "../uartUtils/include/uartUtils.h"

#include "../interface/include/interface.h"
#include "../interface/include/interfaceDescriptor.h"

#define TAG "I2C Interface Descrtiptor "

static const char* i2cInterfaceName = I2C_INTERFACE_HEADER_NAME; 
static const char* i2cInterfaceCommand = INTERFACE_HEADER I2C_INTERFACE_HEADER; 
static const char* i2cInterfaceDescriptort = I2C_INTERFACE_DESCRIPTOR; 

static InterfaceDescriptor i2cInterfaceDescriptor;

InterfaceDescriptor* getI2cInterfaceDescriptor(void){
    return &i2cInterfaceDescriptor;
}

void initI2cInterfaceDescriptor(void){
    InterfaceList *list;
    uint8_t index;
    list = getInterfaceList();
    index = list->currentIndex;

    if (!i2cInterfaceDescriptor.isInit){
        i2cInterfaceDescriptor.isInit = true;
        i2cInterfaceDescriptor.index = index;
        i2cInterfaceDescriptor.name = getInterfaceName(i2cInterfaceName);
        i2cInterfaceDescriptor.command = getInterfaceCommand(i2cInterfaceCommand);
        i2cInterfaceDescriptor.description = getInterfaceDescription(i2cInterfaceDescriptort);    
    }
}

void printI2cInterfaceDescriptor(void){
    printDeviceLine();
    printHelpTitle(INTERFACE_HEADER, I2C_INTERFACE_HEADER,"     ", I2C_INTERFACE_HEADER_NAME);
    printDeviceLine();
    printTableCode("help : "I2C_HELP_HEADER,0x00000,0x00000);
    printTableCode("code error",0x00000,0x20104);
    printTableBlank();
    printTableCode("detect : "I2C_DETECT_HEADER,0x00000,0x00000); 
    printTableCode("code error",0x00000,0x20104);
    printDeviceStar();
}