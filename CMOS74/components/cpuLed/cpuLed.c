#include <stdio.h>
#include "cpuLed.h"

#include "sdkconfig.h"

#include "driver/gpio.h"

#include "esp_event.h"
#include "esp_log.h"

#include "../charUtils/include/charUtils.h"

#include "../../../../esp-idf/components/esp_driver_gpio/include/driver/gpio.h"

static const char *TAG = "CPU_LED";

led_config_t* get_my_leds (int led){
    return &my_leds[led];
}

void led_blink_task(void *pvParameters){
    led_config_t *config = (led_config_t*)pvParameters;

    ESP_LOGI(TAG, "Démarrage de la tâche pour %s sur le GPIO %d (Vitesse : %ld ms)", 
             config->led_name, config->gpio_pin, config->delay_ms);
    
    while (1){
        gpio_set_level(config->gpio_pin,1);
        vTaskDelay(pdMS_TO_TICKS(config->delay_ms));

        gpio_set_level(config->gpio_pin,0);
        vTaskDelay(pdMS_TO_TICKS(config->delay_ms));
    }
    vTaskDelete(NULL);
}    

