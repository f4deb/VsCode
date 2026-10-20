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

InterfaceDescriptor getLedInterfaceDescriptor(void){
    return ledInterfaceDescriptor;
}

void initLedInterfaceDesriptor(){
    InterfaceList *list;
    uint8_t index;
    list = getInterfaceList();
    index = list->currentIndex;

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
    printTableCode("help : "HELP_CPU_LED_HEADER,0x100,0x200);
    printTableBlank();
    printTableLine("Name  : "GET_CPU_LED_NAME_HEADER,"input : 2","Ouput : 16"," ");
    printTableLine("Led index ","        HEX2"," "," ");
    printTableLine("Name","            "," Text12"," ");
    printTableLine("code Error"," ","        HEX4"," ");
    printTableBlank();
    printTableLine("Time : t","input : 7","Ouput : 4 "," ");
    printTableLine("Led index","        HEX2"," "," ");
    printTableLine("Separator ","        HEX1"," "," ");
    printTableLine("Time Value","        DEC4"," "," ");
    printTableLine("code Error"," ","        HEX4"," ");
    printTableBlank();
    printTableLine("Blink : b","input : 6","Ouput : 4 "," ");
    printTableLine("Led index","        HEX2"," "," ");
    printTableLine("Separator ","        HEX1"," "," ");
    printTableLine("Ratio Value","        DEC3"," "," ");
    printTableLine("code Error"," ","        HEX4"," ");
    printTableBlank();
    printTableLine("Set Led : w","input : 4","Ouput : 4 "," ");
    printTableLine("Led index","        HEX2"," "," ");
    printTableLine("Led Value","        HEX2"," "," ");
    printTableLine("code Error"," ","        HEX4"," ");
    printTableBlank();
    printTableLine("Read Led : r","input : 2","Ouput : 6 "," ");
    printTableLine("Led index","        HEX2"," "," ");
    printTableLine("Led Statut"," ","        HEX2"," ");
    printTableLine("code Error"," ","        HEX4"," ");          
    printDeviceLine();

    initLedInterfaceDesriptor();

}