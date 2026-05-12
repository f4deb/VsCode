#include <stdio.h>
#include <string.h>
#include "uartUtils.h"

#include "sdkconfig.h"

#include "esp_event.h"
#include "esp_log.h"

#include "../charUtils/include/charUtils.h"

#include "../uartCommand/include/uartCommand.h"
#include "../../../../esp-idf/components/esp_driver_uart/include/driver/uart.h"

#define TAG "CPU Led Interface"


void uartDataBack(char status[50]){

        // Write data back to the UART
        uart_write_bytes(COMMAND_UART_PORT_NUM, status, strlen(status));
        status [0] = LF;
        status [1] = '\0';
        uart_write_bytes(COMMAND_UART_PORT_NUM, status, strlen(status));
}