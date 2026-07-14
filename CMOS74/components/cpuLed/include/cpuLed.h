#ifndef CPU_LED_H
#define CPU_LED_H

#include <stdint.h>
#include "driver/gpio.h"

#define CPU_LED_DEBUG 0

#define LED1_RED_GPIO CONFIG_LED1_RED_GPIO
#define LED1_GREEN_GPIO CONFIG_LED1_GREEN_GPIO
#define LED2_RED_GPIO CONFIG_LED2_RED_GPIO
#define LED2_GREEN_GPIO CONFIG_LED2_GREEN_GPIO

#define LED1 0
#define LED2 1

#define LED_RED 0
#define LED_GREEN 1

#define LED_1_GPIO 2
#define LED_2_GPIO 4
#define LED_3_GPIO 5
#define LED_4_GPIO 12

typedef struct 
{
    uint8_t value;
    uint8_t pinNumber;
    uint8_t status;
    uint32_t period;
    uint8_t ratio;
}LedColor;

typedef struct cpuLed
{
    uint8_t value;
    LedColor Red,Green;
}CpuLed;


static CpuLed led1;
static CpuLed led2;



CpuLed* getLed1(void);
CpuLed* getLed2(void);

typedef struct {
    gpio_num_t gpio_pin;
    uint32_t delay_ms;
    const char *led_name;
    } led_config_t;

static led_config_t my_leds[] = {
    {.gpio_pin = LED_1_GPIO, .delay_ms = 100, .led_name = "LedRouge1"},
    {.gpio_pin = LED_2_GPIO, .delay_ms = 500, .led_name = "LedVert1"},
    {.gpio_pin = LED_3_GPIO, .delay_ms = 1000, .led_name = "LedRouge2"},
    {.gpio_pin = LED_4_GPIO, .delay_ms = 5000, .led_name = "LedVert2"}
};





uint32_t getTimeBlink (CpuLed* led,uint8_t color);
uint32_t getRatioBlink (CpuLed* led,uint8_t color);

led_config_t* get_my_leds (int led);


void led_blink_task(void *pvParameters);


void setTime (uint32_t value);
void setPeriodBlink (CpuLed* led,uint8_t color,uint32_t value);

void setRatioBlink (CpuLed* led,uint8_t color,uint8_t value);

void configure_led(void);
void blinkCpuLed(CpuLed* led, uint8_t color);

void printCpuLed(void);
void setCpuLed(CpuLed* led,uint8_t color,uint8_t status);
uint8_t getCpuLed(CpuLed* led, uint8_t color);


#endif