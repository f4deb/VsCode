/* Main */

#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "sdkconfig.h"
#include "driver/gpio.h"

#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_dev.h"
#include "esp_lcd_panel_ssd1306.h"

#include "esp_err.h"
#include "esp_log.h"
#include "esp_console.h"
#include "esp_vfs_fat.h"

#include "driver/uart.h"
#include "driver/gpio.h"

#include "argtable3/argtable3.h"
#include "driver/i2c_master.h"


#include "../components/cpuLed/include/cpuLed.h"
#include "../components/charUtils/include/charUtils.h"
#include "../components/i2c/include/i2cTools.h"
#include "../components/interface/include/interface.h"
#include "../components/interface/include/interfaceDescriptor.h"
#include "../components/led_strip/include/led_strip.h"
#include "../components/uartCommand/include/uartCommand.h"

/*

#include "../components/uartCommand/include/uartCommand.h"
#include "../components/clock/include/clock.h"
#include "../components/Oled/include/Oled.h"
#include "../components/I2c/include/I2c.h"
#include "../components/8IoButtonBoard/include/8IoButtonBoard.h"

*/

static const char *TAG= "Main : ";

#define LED_1_GPIO 2
#define LED_2_GPIO 4
#define LED_3_GPIO 5
#define LED_4_GPIO 12

#define GPIO_OUTPUT_PIN_SEL ((1ULL<<LED_1_GPIO)|(1ULL<<LED_2_GPIO)|(1ULL<<LED_3_GPIO)|(1ULL<<LED_4_GPIO))

typedef struct {
    gpio_num_t gpio_pi;
    uint32_t delay_ms;
    const char *led_name;
    } led_config_t;

static led_config_t my_leds[] = {
    {.gpio_pi = LED_1_GPIO, .delay_ms = 200, .led_name = "LedRouge1"},
    {.gpio_pi = LED_2_GPIO, .delay_ms = 500, .led_name = "LedVert1"},
    {.gpio_pi = LED_3_GPIO, .delay_ms = 1000, .led_name = "LedRouge2"},
    {.gpio_pi = LED_4_GPIO, .delay_ms = 5000, .led_name = "LedVert2"}
};


void led_blink_task(void *pvParameters){
    led_config_t *config = (led_config_t*)pvParameters;

    ESP_LOGI(TAG, "Démarrage de la tâche pour %s sur le GPIO %d (Vitesse : %ld ms)", 
             config->led_name, config->gpio_pin, config->delay_ms);
    
    while (1){
        gpio_set_level(config->gpio_pi,1);
        vTaskDelay(pdMS_TO_TICKS(config->delay_ms));

        gpio_set_level(config->gpio_pi,0);
        vTaskDelay(pdMS_TO_TICKS(config->delay_ms));
    }
    vTaskDelete(NULL);
}    

void init(){

    /* Configure the peripheral according to the LED type */
    configure_led();

    I2cBusInit();  

    gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = GPIO_OUTPUT_PIN_SEL,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE
    };
    gpio_config(&io_conf);

    //i2c_dev_pcf8574_init();
//printDeviceLine();
    //initClock();
    //UART COMMAND Task
    xTaskCreate(command_uart_task, 
                "uart_command_task", 
                COMMAND_TASK_STACK_SIZE, 
                NULL,
                2, 
                NULL);
  
    xTaskCreate(led_blink_task, 
                "Cpu Led1 Task", 
                COMMAND_TASK_STACK_SIZE, 
                &my_leds[0],
                5, 
                NULL); 
    xTaskCreate(led_blink_task, 
                "Cpu Led2 Task", 
                COMMAND_TASK_STACK_SIZE, 
                &my_leds[1],
                5, 
                NULL);    
    xTaskCreate(led_blink_task, 
                "Cpu Led3 Task", 
                COMMAND_TASK_STACK_SIZE, 
                &my_leds[2],
                5, 
                NULL);              
    xTaskCreate(led_blink_task, 
                "Cpu Led4 Task", 
                COMMAND_TASK_STACK_SIZE, 
                &my_leds[3],
                5, 
                NULL);                 
/*
    // CLOCK Task
    xTaskCreate(clock_task,
                "clock_task",
                CLOCK_TASK_STACK_SIZE,
                NULL, 
                4, 
                NULL);

    // IOBUTTONBOARD TASK
    xTaskCreate(ioButtonBoard_task,
                "IO BUTTON BOARD task",
                IO_BUTTUN_BOARD_TASK_SIZE,
                NULL, 
                3, 
                NULL);     */          

    // INTERFACE TASK
    xTaskCreate(interface_task,
                "interface_task",
                INTERFACE_TASK_STACK_SIZE,
                NULL,
                3,
                NULL);    
}

void app_main(void){
    init();
    i2cDetect();
    
    //   Blink Task
    while (1) {
        //printCpuLed();
    }
}