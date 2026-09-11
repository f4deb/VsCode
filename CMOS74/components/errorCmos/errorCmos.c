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

void printError (uint32_t codeError, uint8_t output){

error_code_t current_state = ERR_COMMAND_INVALID;


    esp_err_t ret = ESP_FAIL;
if (ret != ESP_OK) {
    printf("I2C driver install failed: %s \n", device_state_to_str(current_state));
}
ESP_LOGE(TAG, "Nouvel état : %s", device_state_to_str(current_state));

}



