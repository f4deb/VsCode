#ifndef ERROR_CMOS_H
#define ERROR_CMOS_H

#include <stdint.h>
#include <string.h>

#include "esp_err.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


// Base offset pour ton composant personnalisé (Bit 17 activé + offset composant)




typedef enum {
    ERROR_BASE = 0x20000,
    ERR_COMMAND_INVALID,
    ERR_SEPARATOR,
    
    CPU_LED_ERR_BASE = ERROR_BASE + 0x00100,
    DEVICE_STATE_CONNECTED,
    DEVICE_STATE_ERROR,

    UART_ERR_BASE = ERROR_BASE +0x00200

} error_code_t;


const char* device_state_to_str(error_code_t errorCode);

void printError (uint32_t codeError, uint8_t output);


#endif