#include "errorCmos.h"

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

#include "esp_log.h"



#define TAG "Error Cmos"

const char* device_state_to_str(error_code_t errorCode) {
    switch (errorCode) {
        case ERR_COMMAND_INVALID:       return "Command Invalid";
        case ERR_SEPARATOR:             return "Pas de separateur -";
        case DEVICE_STATE_CONNECTED:    return "CONNECTED";
        case DEVICE_STATE_ERROR:        return "ERROR";
        default:                        return "UNKNOWN";
    }
}

void printError (error_code_t codeError, uint8_t output){
    if (output == NULL){
        return;
    }
    if ((output & BIT(0)) != 0){
        ESP_LOGE(TAG, "Nouvel état1 : %d", output);
    }
    if ((output & BIT(1)) != 0){
        printf("Nouvel état2 : %d", output);
            printf("hello\n");
    }
    if ((output & BIT(2)) != 0){
        ESP_LOGE(TAG, "BAD OUTPUT : %d", output);
    }
        if ((output & BIT(3)) != 0){
        ESP_LOGE(TAG, "BAD OUTPUT : %d", output);
    }
}   //    printError (ERR_SEPARATOR ,OUTPUT_DEBUG | OUTPUT_COMMAND );
