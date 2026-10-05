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

void cpuLedInterfaceDescriptor(void){  
    printDeviceLine();
    printHelpTitle(INTERFACE_HEADER, CPU_LED_INTERFACE_HEADER,"     ", CPU_LED_INTERFACE_HEADER_NAME);
    printDeviceLine();
    printTableLine("help : h","input : 0","Ouput : 0 "," ");
    printTableBlank();
    printTableLine("Name  : n","input : 2","Ouput : 16"," ");
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
}