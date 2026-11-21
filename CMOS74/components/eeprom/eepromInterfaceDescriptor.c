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
    printHelpTitle(eepromInterfaceDescriptor.command,  " / ", eepromInterfaceDescriptor.name, eepromInterfaceDescriptor.description);
    printDeviceLine();
    printTableCode("help : "EEPROM_HELP_HEADER,0x00000,0x00000);
    printTableBlank();
    printTableCode("Write Block Eeprom  : "EEPROM_BLOCK_WRITE_HEADER,0x00000,0x00000);
    printTableCode("Start Address to write",0x10104,0x00000);
    printTableCode("separator -",0x40000,0x00000);
    printTableCode("16 bytes to write  -",0x010132,0x00000);
    printTableCode("code error",0x00000,0x20104); 
    printTableBlank();
    printTableCode("Write byte Eeprom  : "EEPROM_BYTE_WRITE_HEADER,0x00000,0x00000);
    printTableCode("Start Address to write",0x10104,0x00000);
    printTableCode("separator -",0x40000,0x00000);
    printTableCode("Byte to write  -",0x010102,0x00000);
    printTableCode("code error",0x00000,0x20104); 
    printTableBlank();
    printTableCode("Eeprom set Adrress : "EEPROM_SET_ADDRESSE_HEADER,0x00000,0x00000); 
    printTableCode("Set EEprom address",0x10104,0x00000);
    printTableCode("code error",0x00000,0x20104);
    printTableBlank();
    printTableCode("Read Eeprom : "EEPROM_READ_BYTE_HEADER,0x00000,0x00000); 
    printTableCode("Address to Read",0x10104,0x00000);
    printTableCode("Return Value",0x00000,0x20102);
    printTableCode("code error",0x00000,0x20104); 
    printTableBlank();
    printTableCode("Read Block Eeprom : "EEPROM_READ_BLOC_ADRESS_HEADER,0x00000,0x00000); 
    printTableCode("Start Address to Read",0x10104,0x00000);
    printTableCode("separator -",0x40000,0x00000);
    printTableCode("Block size to read",0x10102,0x00000);
    printTableCode("Return Value",0x00000,0x20102);
    printTableCode("code error",0x00000,0x20104); 
    printTableBlank();
    printTableCode("Eeprom set Adrress : "EEPROM_READ_ALL_HEADER,0x00000,0x00000); 
    printTableCode("code error",0x00000,0x20104);
    printDeviceLine();
}

