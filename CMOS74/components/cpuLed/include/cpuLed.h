#ifndef CPU_LED_H
#define CPU_LED_H

#include <stdint.h>
#include "driver/gpio.h"

#define CPU_LED_DEBUG 0

#define LED1_RED_GPIO CONFIG_LED1_RED_GPIO
#define LED1_GREEN_GPIO CONFIG_LED1_GREEN_GPIO
#define LED2_RED_GPIO CONFIG_LED2_RED_GPIO
#define LED2_GREEN_GPIO CONFIG_LED2_GREEN_GPIO



typedef struct {
    gpio_num_t gpio_pin;
    long delay_ms;
    uint8_t ratio_ms;
    const char *led_name;
    uint8_t index;
    } led_config_t;

static led_config_t my_leds[] = {
    {.gpio_pin = LED1_GREEN_GPIO, .delay_ms = 100, .ratio_ms = 50, .index = 0, .led_name = "LedVert1"},
    {.gpio_pin = LED1_RED_GPIO, .delay_ms = 200, .ratio_ms = 50, .index = 1, .led_name = "LedRouge1"},
    {.gpio_pin = LED2_GREEN_GPIO, .delay_ms = 1000, .ratio_ms = 50, .index = 2, .led_name = "LedVert2"},
    {.gpio_pin = LED2_RED_GPIO, .delay_ms = 5000, .ratio_ms = 50, .index = 3, .led_name = "LedRouge2"}
};

led_config_t* get_my_leds (int led);

void led_blink_task(void *pvParameters);

#endif