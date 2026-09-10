#include <stdio.h>
#include "logCmos.h"

#include "esp_err.h"
#include "esp_log.h"


void init_custom_logs(void){
        s_previous_log_vprintf = esp_log_set_vprintf(custom_log_vprintf);

}



