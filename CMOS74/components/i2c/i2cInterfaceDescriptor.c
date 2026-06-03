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

void i2cInterfaceDescriptor(void){
    printDeviceLine();
    printHelpTitle(INTERFACE_HEADER, I2C_INTERFACE_HEADER,"     ", I2C_INTERFACE_HEADER_NAME);
    printDeviceLine();
    printTableBLine("help : h","input : 0","Ouput : 0 "," ");
    printTableBlank();
    printTableBLine("detect : c","input : 0","Ouput : 0 "," "); 
    printDeviceStar();
}