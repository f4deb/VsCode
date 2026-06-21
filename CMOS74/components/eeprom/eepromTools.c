#include <stdio.h>
#include <string.h>
#include "eepromTools.h"
#include "eepromInterface.h"
#include "eepromInterfaceDescriptor.h"

#include "sdkconfig.h"

#include "esp_event.h"
#include "esp_log.h"

#include "../i2c/include/i2cTools.h"

#include "../driverCmos/eeprom/include/i2cEeprom.h"

uint8_t buf[LENGTH];
uint32_t block_addr = 0x0010;
uint8_t read_buf[LENGTH];


static i2c_eeprom_handle_t eeprom_handle;


static void disp_buf(uint8_t *buf, int len)
{
    int i;
    for (i = 0; i < len; i++) {
        printf("%02x ", buf[i]);
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

void  eepromInit(void){
         
    i2c_eeprom_config_t eeprom_config = {
        .eeprom_device.scl_speed_hz = MASTER_FREQUENCY_400,
        .eeprom_device.device_address = 0x50,
        .addr_wordlen = 2,
        .write_time_ms = 10,
    };


    for (int i = 0; i < LENGTH; i++) {
        buf[i] = i;
    }
    ESP_ERROR_CHECK(i2c_eeprom_init(getI2cBus(), &eeprom_config, &eeprom_handle));

 /*while (1) {
        ESP_ERROR_CHECK(i2c_eeprom_write(eeprom_handle, block_addr, buf, LENGTH));
        // Needs wait for eeprom hardware done, referring from datasheet
        i2c_eeprom_wait_idle(eeprom_handle);
        ESP_ERROR_CHECK(i2c_eeprom_read(eeprom_handle, block_addr, read_buf, LENGTH));
        disp_buf(read_buf, LENGTH);
        vTaskDelay(50);
    }
*/
}

void writeEeprom(void){
     ESP_ERROR_CHECK(i2c_eeprom_write(eeprom_handle, block_addr, buf, LENGTH));
    // Needs wait for eeprom hardware done, referring from datasheet
    i2c_eeprom_wait_idle(eeprom_handle);
    vTaskDelay(50);
}

void readEeprom(void){
    ESP_ERROR_CHECK(i2c_eeprom_read(eeprom_handle, block_addr, read_buf, LENGTH));
    disp_buf(read_buf, LENGTH);
    vTaskDelay(50);
}