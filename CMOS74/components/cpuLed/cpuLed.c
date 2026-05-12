#include <stdio.h>
#include "cpuLed.h"

#include "sdkconfig.h"

#include "esp_event.h"
#include "esp_log.h"

#include "../charUtils/include/charUtils.h"

#include "../../../../esp-idf/components/esp_driver_gpio/include/driver/gpio.h"

static const char *TAG = "CPU_LED";

void initCpu2Led(CpuLed* led, int reference ){

    if (reference == LED1 ) { 
        led->value = LED1;
        led->Red.value = LED_RED;
        led->Green.value = LED_GREEN;

        led->Red.status = 0;
        led->Red.pinNumber = CONFIG_LED1_RED_GPIO;
        led->Red.period = CONFIG_LED1_RED_PERIOD;
        led->Red.ratio = CONFIG_LED1_RED_RATIO;

        led->Green.status=0;
        led->Green.pinNumber = CONFIG_LED1_GREEN_GPIO;
        led->Green.period = CONFIG_LED1_GREEN_PERIOD;
        led->Green.ratio = CONFIG_LED1_GREEN_RATIO;
    }
    else if (reference == LED2 ) {
        led->value = LED2;
        led->Red.value = LED_RED;
        led->Green.value = LED_GREEN;

        led->Red.status = 0;
        led->Red.pinNumber = CONFIG_LED2_RED_GPIO;
        led->Red.period = CONFIG_LED2_RED_PERIOD;
        led->Red.ratio = CONFIG_LED2_RED_RATIO;

        led->Green.status=0;
        led->Green.pinNumber = CONFIG_LED2_GREEN_GPIO;
        led->Green.period = CONFIG_LED2_GREEN_PERIOD;
        led->Green.ratio = CONFIG_LED2_GREEN_RATIO;
    }    
}

void initCpuLed (void){
    initCpu2Led(&led1, LED1);
    initCpu2Led(&led2, LED2);
}

uint32_t getTimeBlink (CpuLed* led,uint8_t color){
    uint32_t result = 0;
        if (color == LED_RED){
            result = led->Red.period;
        }
        else if (color == LED_GREEN){
            result = led->Green.period;        
        } 
    return result;
}

uint32_t getRatioBlink (CpuLed* led,uint8_t color){
    uint32_t result = 0;
        if (color == LED_RED){
            result = led->Red.ratio;
        }
        else if (color == LED_GREEN){
            result = led->Green.ratio;        
        } 
    return result;
}

void setTime (uint32_t value){
}


void setPeriodBlink (CpuLed* led,uint8_t color,uint32_t value){
        if (color == LED_RED){
            led->Red.period = value;
        }
        else if (color == LED_GREEN){
            led->Green.period = value;        
        } 
}

void setRatioBlink (CpuLed* led,uint8_t color,uint8_t value){
    if (color == LED_RED){
        led->Red.ratio = value;
    }
    else if (color == LED_GREEN){
        led->Green.ratio = value;        
    } 

    if (CPU_LED_DEBUG) ESP_LOGE(TAG, "LED RATIO %02d", value);
}

uint8_t getLedGpio (CpuLed* led,uint8_t color){
    uint8_t result = 0;
        if (color == LED_RED){
            result = led->Red.pinNumber;
        }
        else if (color == LED_GREEN){
            result = led->Green.pinNumber;        
        } 
    return result;
}

uint32_t getLedPeriod(CpuLed* led,uint8_t color){
    uint32_t result = 0;
    if (color == LED_RED){
            result = led->Red.period;
        }
        else if (color == LED_GREEN){
            result = led->Green.period;        
        } 
    return result;
}

uint8_t getLedRatio(CpuLed* led,uint8_t color){
    uint8_t result = 0;
    if (color == LED_RED){
            result = led->Red.ratio;
        }
        else if (color == LED_GREEN){
            result = led->Green.ratio;        
        } 
    return result;
}

uint8_t getLedStatus(CpuLed* led,uint8_t color){
    uint8_t result = 0;
    if (color == LED_RED){
            result = led->Red.status;
        }
        else if (color == LED_GREEN){
            result = led->Green.status;        
        } 
    return result;
}

void setLedStatus (CpuLed* led,uint8_t color,uint8_t status) {        
        if (color == LED_RED){
            led->Red.status = status;
        }
        else if (color == LED_GREEN){
            led->Green.status = status;        
        } 
}

void initLed(CpuLed* led, uint8_t color){
    if (CPU_LED_DEBUG) ESP_LOGI(TAG, "Cpu Led configured to blink GPIO LED!");
    gpio_reset_pin(getLedGpio(led, color));
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(getLedGpio(led, color), GPIO_MODE_OUTPUT);

    gpio_set_level(getLedGpio(led, color), 1);
}

void configure_led(void){
    initCpuLed();
    initLed(&led1,LED_GREEN);
    initLed(&led1,LED_RED);
    initLed(&led2,LED_GREEN);
    initLed(&led2,LED_RED);
}

void blinkCpuLed(CpuLed* led, uint8_t color){
    uint8_t status;

    if (CPU_LED_DEBUG) ESP_LOGI(TAG, "Turning the LED %s!", getLedStatus(led, color) == true ? "OFF" : "ON");

    /* Toggle the LED state */

	//printf("l adresse de led est : %p\n",&led);
	//printf("l adresse de led1 est : %p\n",&led1);

    status = getLedStatus(led, color);

    int ratio = getLedRatio(led, color); 
    
    if ((ratio == 0) || (ratio == 99)){
            if (ratio == 0) { status = 0;}
            else status = 1;
            setLedStatus(led, color, status);
            gpio_set_level(getLedGpio(led, color), getLedStatus(led, color));
            vTaskDelay(1);
    }
    else if ((ratio>0 )&&(ratio<99)){

        setLedStatus(led, color, !status);

        /* Set the GPIO level according to the state (LOW or HIGH)*/
        gpio_set_level(getLedGpio(led, color), getLedStatus(led, color));


        if (getLedStatus(led,color)) vTaskDelay(pdMS_TO_TICKS(getLedPeriod(led,color) * getLedRatio(led,color) /100));
        else vTaskDelay(pdMS_TO_TICKS(getLedPeriod(led,color) - (getLedPeriod(led,color) * getLedRatio(led,color) /100)));
    }
}

CpuLed* getLed1(void){
    return &led1;
}

CpuLed* getLed2(void){
    return &led2;
}

/**********************
 * Device
 **********************/

 void printCpuLed(void){
    blinkCpuLed( getLed1(),  LED_GREEN);            
    blinkCpuLed( getLed1(),  LED_RED);           
    blinkCpuLed( getLed2(),  LED_GREEN);            
    blinkCpuLed( getLed2(),  LED_RED);    
 }

void setCpuLed(CpuLed* led,uint8_t color,uint8_t ledStatus){
    if (CPU_LED_DEBUG) ESP_LOGI(TAG, "Turning the LED %s!", ledStatus == true ? "ON" : "OFF");
    setLedStatus(led, color, ledStatus);
}

uint8_t getCpuLed(CpuLed* led, uint8_t color){
    if (CPU_LED_DEBUG) ESP_LOGE(TAG, "test command");
    uint8_t result = getLedStatus(led, color);

    //if (CPU_LED_DEBUG) ESP_LOGI(TAG_CPU_LED, "Return the LED Status %s!", s_led1_red_state == true ? "ON" : "OFF");
    return result;
}