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
    printTableBLine("help : h","input : 0","Ouput : 0 "," ");
    printTableBlank();
    printTableBLine("Name  : n","input : 3","Ouput : Text "," ");
    printTableBLine("Led index ","        HEX2"," "," ");
    printTableBLine("Name","            "," Text"," ");
    printTableBLine("code Error"," ","        HEX2"," ");
    printTableBlank();
    printTableBLine("Time : t","input : 8","Ouput : 2 "," ");
    printTableBLine("Led Selection","        HEX2"," "," ");
    printTableBLine("Separator ","        HEX1"," "," ");
    printTableBLine("Time Value","        DEC4"," "," ");
    printTableBLine("code Error"," ","        HEX2"," ");
    printTableBlank();
    printTableBLine("Blink : b","input : 8","Ouput : 2 "," ");
    printTableBLine("Led Selection","        HEX2"," "," ");
    printTableBLine("Separator ","        HEX1"," "," ");
    printTableBLine("Ratio Value","        DEC3"," "," ");
    printTableBLine("code Error"," ","        HEX2"," ");
    printTableBlank();
    printTableBLine("Set Led : w","input : 6","Ouput : 2 "," ");
    printTableBLine("Led Selection","        HEX2"," "," ");
    printTableBLine("Color Selection","        HEX2"," "," ");
    printTableBLine("Led Value","        DEC2"," "," ");
    printTableBLine("code Error"," ","        HEX2"," ");
    printTableBlank();
    printTableBLine("Read Led : r","input : 4","Ouput : 4 "," ");
    printTableBLine("Led Selection","        HEX2"," "," ");
    printTableBLine("Color Selection","        HEX2"," "," ");
    printTableBLine("Led Statut"," ","        HEX2"," ");
    printTableBLine("code Error"," ","        HEX2"," ");          
    printDeviceLine();
}