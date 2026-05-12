#ifndef CPU_LED_H
#define CPU_LED_H

#include <stdint.h>

#define CPU_LED_DEBUG 0

#define LED1_RED_GPIO CONFIG_LED1_RED_GPIO
#define LED1_GREEN_GPIO CONFIG_LED1_GREEN_GPIO
#define LED2_RED_GPIO CONFIG_LED2_RED_GPIO
#define LED2_GREEN_GPIO CONFIG_LED2_GREEN_GPIO

#define LED1 0
#define LED2 1

#define LED_RED 0
#define LED_GREEN 1

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


uint32_t getTimeBlink (CpuLed* led,uint8_t color);
uint32_t getRatioBlink (CpuLed* led,uint8_t color);

void setTime (uint32_t value);
void setPeriodBlink (CpuLed* led,uint8_t color,uint32_t value);

void setRatioBlink (CpuLed* led,uint8_t color,uint8_t value);

void configure_led(void);
void blinkCpuLed(CpuLed* led, uint8_t color);

void printCpuLed(void);
void setCpuLed(CpuLed* led,uint8_t color,uint8_t status);
uint8_t getCpuLed(CpuLed* led, uint8_t color);


#endif