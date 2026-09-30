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


#include "../components/charUtils/include/charUtils.h"
#include "../components/cpuLed/include/cpuLed.h"
#include "../components/errorStore/include/errorStore.h"
#include "../components/errorStore/include/errorStoreInterface.h"

#include "../components/eeprom/include/eepromTools.h"

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

#define GPIO_OUTPUT_PIN_SEL ((1ULL<<LED1_GREEN_GPIO)|(1ULL<<LED1_RED_GPIO)|(1ULL<<LED2_GREEN_GPIO)|(1ULL<<LED2_RED_GPIO))

void init(){

    errorStoreInit();
/*
ESP_ERROR_CHECK(error_store_init());

 error_store_write(ESP_FAIL, "titi");
 error_store_write(ESP_ERR_TIMEOUT, "TiTi");

    
// Lecture des erreurs
    error_log_entry_t logs[MAX_ERROR_LOGS];
    size_t count = 0;

    if (error_store_read_all(logs, &count) == ESP_OK) {
        ESP_LOGI(TAG, "Nombre d'erreurs en mémoire : %zu", count);
        for (size_t i = 0; i < count; i++) {
            ESP_LOGI(TAG, "[%lu ms] Code: 0x%x | Msg: %s",
                     logs[i].timestamp, logs[i].err_code, logs[i].message);
        }
    }
*/


    /* Configure the peripheral according to the LED type */
    //configure_led();

    I2cBusInit();  

    gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = GPIO_OUTPUT_PIN_SEL,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE
    };
    gpio_config(&io_conf);

    eepromInit();

    //i2c_dev_pcf8574_init();
//printDeviceLine();
    //initClock();
    //UART COMMAND Task
    xTaskCreate(command_uart_task, 
                "uart_command_task", 
                COMMAND_TASK_STACK_SIZE, 
                NULL,
                6, 
                NULL);
  
    xTaskCreate(led_blink_task, 
                "Cpu Led vert 1 Task", 
                LED_TASK_STACK_SIZE, 
                get_my_leds(0),
                2, 
                NULL); 
    xTaskCreate(led_blink_task, 
                "Cpu Led rouge 1 Task", 
                LED_TASK_STACK_SIZE, 
                get_my_leds(1),
                2, 
                NULL);    
    xTaskCreate(led_blink_task, 
                "Cpu Led3 Task", 
                LED_TASK_STACK_SIZE, 
                get_my_leds(2),
                2, 
                NULL);              
    xTaskCreate(led_blink_task, 
                "Cpu Led4 Task", 
                LED_TASK_STACK_SIZE, 
                get_my_leds(3),
                2, 
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
                4,
                NULL);    
}

void app_main(void){
    init();
    i2cDetect();
}