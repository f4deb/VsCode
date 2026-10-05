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

void eepromInterfaceDescriptor(void){
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