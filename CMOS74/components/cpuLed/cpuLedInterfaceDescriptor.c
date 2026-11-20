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

#define TAG "CPU Led Interface Descrtiptor "

static const char* ledInterfaceName = CPU_LED_INTERFACE_HEADER_NAME; 
static const char* ledInterfaceCommand = INTERFACE_HEADER CPU_LED_INTERFACE_HEADER; 
static const char* ledInterfaceDescriptort = CPU_LED_INTERFACE_DESCRIPTOR; 

static InterfaceDescriptor ledInterfaceDescriptor;

InterfaceDescriptor* getLedInterfaceDescriptor(void){
    return &ledInterfaceDescriptor;
}

void initLedInterfaceDesriptor(){
    InterfaceList *list;
    uint8_t index;
    list = getInterfaceList();
    index = list->indexMax;

    list->map[index] = *getLedInterfaceDescriptor();
    list->currentIndex++;
    list->indexMax = list->currentIndex;

    if (!ledInterfaceDescriptor.isInit){
        ledInterfaceDescriptor.isInit = true;
        ledInterfaceDescriptor.index = index;
        ledInterfaceDescriptor.name = getInterfaceName(ledInterfaceName);
        ledInterfaceDescriptor.command = getInterfaceCommand(ledInterfaceCommand);
        ledInterfaceDescriptor.description = getInterfaceDescription(ledInterfaceDescriptort);    
    }

}

void cpuLedInterfaceDescriptor(void){  

    printDeviceLine();
    printHelpTitle(ledInterfaceDescriptor.command,  " / ", ledInterfaceDescriptor.name, ledInterfaceDescriptor.description);
    printDeviceLine();
    printTableCode("help : "HELP_CPU_LED_HEADER,0x00000,0x00000);
    printTableBlank();
    printTableCode("Get Name  : "GET_CPU_LED_NAME_HEADER,0x00000,0x00000);
    printTableCode("Led index",0x10102,0x00000);
    printTableCode("Return",0x00000,0x30000); 
    printTableBlank();
    printTableCode("Set time blink "SET_TIME_BLINK_HEADER,0x00000,0x00000);
    printTableCode("Led index",0x10102,0x00000);
    printTableCode("Separator ",0x40101,0x00000);
    printTableCode("Time Value",0x10204,0x00000);
    printTableCode("code Error",0x00000,0x20104);
    printTableBlank();
    printTableCode("Blink Ratio : "SET_RATIO_BLINK_HEADER,0x00000,0x00000);
    printTableCode("Led index",0x10102,0x00000);
    printTableCode("Separator ",0x40101,0x00000);
    printTableCode("Ratio Value",0x10203,0x00000);
    printTableCode("code Error",0x00000,0x20104);
    printTableBlank();
    printTableCode("Set Led : "SET_CPU_LED_HEADER,0x00000,0x00000);
    printTableCode("Led index",0x10102,0x00000);
    printTableCode("Separator ",0x40101,0x00000);
    printTableCode("Led Value",0x10102,0x00000);
    printTableCode("code Error",0x00000,0x20104);
    printTableBlank();
    printTableCode("Read Led : "GET_CPU_LED_HEADER,0x00000,0x00000);
    printTableCode("Led index",0x10102,0x00000);
    printTableCode("Led Statut",0x00000,0x20102);
    printTableCode("code Error",0x00000,0x20104);          
    printDeviceLine();
}