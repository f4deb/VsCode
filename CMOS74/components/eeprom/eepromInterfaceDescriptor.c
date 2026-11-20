#include <stdio.h>
#include <string.h>
#include "eepromTools.h"
#include "eepromInterface.h"
#include "eepromInterfaceDescriptor.h"

#include "sdkconfig.h"

#include "esp_event.h"
#include "esp_log.h"

#include "../charUtils/include/charUtils.h"
#include "../uartUtils/include/uartUtils.h"

#include "../interface/include/interface.h"
#include "../interface/include/interfaceDescriptor.h"

#define TAG "EEPROM Interface Descrtiptor "

static const char* eepromInterfaceName = EEPROM_INTERFACE_HEADER_NAME; 
static const char* eepromInterfaceCommand = INTERFACE_HEADER EEPROM_INTERFACE_HEADER; 
static const char* eepromInterfaceDescriptort = EEPROM_INTERFACE_DESCRIPTOR; 

static InterfaceDescriptor eepromInterfaceDescriptor;

InterfaceDescriptor* getEepromInterfaceDescriptor(void){
    return &eepromInterfaceDescriptor;
}

void initEepromInterfaceDescriptor(void){
    InterfaceList *list;
    uint8_t index;
    list = getInterfaceList();
    index = list->currentIndex;

    if (!eepromInterfaceDescriptor.isInit){
        eepromInterfaceDescriptor.isInit = true;
        eepromInterfaceDescriptor.index = index;
        eepromInterfaceDescriptor.name = getInterfaceName(eepromInterfaceName);
        eepromInterfaceDescriptor.command = getInterfaceCommand(eepromInterfaceCommand);
        eepromInterfaceDescriptor.description = getInterfaceDescription(eepromInterfaceDescriptort);    
    }
}







void printEepromInterfaceDescriptor(void){
    printDeviceLine();
    printHelpTitle(INTERFACE_HEADER, EEPROM_INTERFACE_HEADER,"     ", EEPROM_INTERFACE_HEADER_NAME);
    printDeviceLine();
    printTableLine("help        : h","input : 0","Ouput : 0 "," ");
    printTableBlank();
    printTableLine("Write Block : W","input : 18","Ouput : 2 "," "); 
    printTableBlank();
    printTableLine("Read Block  : W","input : 18","Ouput : 2 "," ");     
    printDeviceStar(); 
}