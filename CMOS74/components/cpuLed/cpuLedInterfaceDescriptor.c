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

char status[100] = "TOTO";


void cpuLedInterfaceDescriptor(void){
    char *str1 = "";
    sprintf(status,"\r" );      
    uartDataBack(status);

    
    printDeviceLine();


    sprintf(status,"| " );
    str1=INTERFACE_HEADER;
    strncat (status,str1,strlen(str1)+1);
    str1=CPU_LED_INTERFACE_HEADER;
    strncat (status,str1,strlen(str1)+1);
    str1="     ";
    strncat (status,str1,strlen(str1)+1);
    str1=CPU_LED_IHEADER_NAME;
    strncat (status,str1,strlen(str1)+1);
    str1="                                ";
    strncat (status,str1,strlen(str1)+1);
    str1="|";
    strncat (status,str1,strlen(str1)+1);
    ESP_LOGE(TAG,"%s",status);
    uartDataBack(status);

    sprintf(status,"|" );
    str1="-";
    for (int i = 0;i < 50 ; i++){
        strncat (status,str1,strlen(str1)+1);
    }
    str1="|";
    strncat (status,str1,strlen(str1)+1);
    ESP_LOGE(TAG,"%s",status);
    uartDataBack(status);
    
    sprintf(status, "| help : h       | input : 0      | Ouput : 0      |");
    ESP_LOGE(TAG,"%s",status);
    uartDataBack(status);

    sprintf(status,"|                |                |                |" ); 
    ESP_LOGE(TAG,"%s",status);
    uartDataBack(status);

    sprintf(status, "| blink : b      | input : 6      | Ouput : 2      |");
    ESP_LOGE(TAG,"%s",status);
    uartDataBack(status);

    sprintf(status, "| Led Selection  |         HEX2   |                |");
    ESP_LOGE(TAG,"%s",status);
    uartDataBack(status);

    sprintf(status, "| Color Selection|         HEX2   |                |");
    ESP_LOGE(TAG,"%s",status);
    uartDataBack(status);

    sprintf(status, "| Ratio Value    |         HEX2   |                |");
    ESP_LOGE(TAG,"%s",status);
    uartDataBack(status);

    sprintf(status, "| code Error     |                |         HEX2   |");
    ESP_LOGE(TAG,"%s",status);
    uartDataBack(status);

    sprintf(status,"|                |                |                |" ); 
    ESP_LOGE(TAG,"%s",status);
    uartDataBack(status);

    sprintf(status, "| Time : t       | input : 8      | Ouput : 2      |");
    ESP_LOGE(TAG,"%s",status);
    uartDataBack(status);

    sprintf(status, "| Led Selection  |         HEX2   |                |");
    ESP_LOGE(TAG,"%s",status);
    uartDataBack(status);

    sprintf(status, "| Color Selection|         HEX2   |                |");
    ESP_LOGE(TAG,"%s",status);
    uartDataBack(status);

    sprintf(status, "| Time Value     |         DEC4   |                |");
    ESP_LOGE(TAG,"%s",status);
    uartDataBack(status);

    sprintf(status, "| code Error     |                |         HEX2   |");
    ESP_LOGE(TAG,"%s",status);
    uartDataBack(status);

    sprintf(status,"|                |                |                |" ); 
    ESP_LOGE(TAG,"%s",status);
    uartDataBack(status);

    sprintf(status, "| Set Led : w    | input : 6      | Ouput : 2      |");
    ESP_LOGE(TAG,"%s",status);
    uartDataBack(status);

    sprintf(status, "| Led Selection  |         HEX2   |                |");
    ESP_LOGE(TAG,"%s",status);
    uartDataBack(status);

    sprintf(status, "| Color Selection|         HEX2   |                |");
    ESP_LOGE(TAG,"%s",status);
    uartDataBack(status);

    sprintf(status, "| Led Value      |         DEC2   |                |");
    ESP_LOGE(TAG,"%s",status);
    uartDataBack(status);

    sprintf(status, "| code Error     |                |         HEX2   |");
    ESP_LOGE(TAG,"%s",status);
    uartDataBack(status);

    sprintf(status,"|                |                |                |" ); 
    ESP_LOGE(TAG,"%s",status);
    uartDataBack(status);

    sprintf(status, "| Read Led : r   | input : 4      | Ouput : 4      |");
    ESP_LOGE(TAG,"%s",status);
    uartDataBack(status);

    sprintf(status, "| Led Selection  |         HEX2   |                |");
    ESP_LOGE(TAG,"%s",status);
    uartDataBack(status);

    sprintf(status, "| Color Selection|         HEX2   |                |");
    ESP_LOGE(TAG,"%s",status);
    uartDataBack(status);

    sprintf(status, "| Led Statut     |                |         HEX2   |");
    ESP_LOGE(TAG,"%s",status);
    uartDataBack(status);

    sprintf(status, "| code Error     |                |         HEX2   |");
    ESP_LOGE(TAG,"%s",status);
    uartDataBack(status);
            
    printDeviceLine();
}