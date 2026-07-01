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

int LENGTH = 48;

static uint8_t write_buf[];
static uint8_t read_buf[];
static uint32_t block_addr = 0;

static i2c_eeprom_handle_t eeprom_handle;


static void disp_buf(uint8_t *write_buf, int len)
{
    int i;
    for (i = 0; i < len; i++) {
        printf("%02x ", write_buf[i]);
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

unsigned char* getReadBuffer(void){
    return read_buf;
}

unsigned char* getWriteBuffer(void){
    return write_buf;
}

void setBlockAddr(uint32_t addr){
    block_addr = addr;
}

void  eepromInit(void){
         
    i2c_eeprom_config_t eeprom_config = {
        .eeprom_device.scl_speed_hz = MASTER_FREQUENCY_400,
        .eeprom_device.device_address = 0x50,
        .addr_wordlen = 2,
        .write_time_ms = 10,
    };


    for (int i = 0; i < LENGTH; i++) {
        write_buf[i] = i*4;
    }
    ESP_ERROR_CHECK(i2c_eeprom_init(getI2cBus(), &eeprom_config, &eeprom_handle));
}

/**
  * @brief write Data to EEprom
  *
  * This function write the "write_buf" into the EEPROM
  *
  * @param value the value to write to the Eeprom
  * @param addr the start address to to the Eeprom 
  * @return codeErr containing the code Erreur to retrun
  */

void writeEeprom(uint8_t value[], uint32_t addr, uint8_t length){
     ESP_ERROR_CHECK(i2c_eeprom_write(eeprom_handle, addr, value, length));
    // Needs wait for eeprom hardware done, referring from datasheet
    i2c_eeprom_wait_idle(eeprom_handle);
    vTaskDelay(50);
}

void readEeprom(void){
    ESP_ERROR_CHECK(i2c_eeprom_read(eeprom_handle, block_addr, read_buf, LENGTH));
    disp_buf(read_buf, LENGTH);
    vTaskDelay(50);
}