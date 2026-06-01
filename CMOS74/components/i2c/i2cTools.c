#include "i2cTools.h"

#include <stdio.h>
#include <string.h>
#include "argtable3/argtable3.h"
#include "driver/i2c_master.h"
#include "esp_console.h"
#include "esp_log.h"


#define I2C_TOOL_TIMEOUT_VALUE_MS (50)
#define ESP_I2C_PORT I2C_NUM_0
#define ESP_I2C_SDA  GPIO_NUM_21
#define ESP_I2C_SCL  GPIO_NUM_22

static uint32_t i2c_frequency = 100 * 1000;
static const char *TAG = "i2ctools";
static i2c_master_bus_handle_t tool_bus_handle; //static i2c_master_bus_handle_t i2c_handle = NULL;
static i2c_master_bus_config_t i2c_bus_config;




i2c_master_bus_handle_t getI2cBus (void){
    return tool_bus_handle;
}
    
uint8_t I2cBusInit(void){
    i2c_master_bus_config_t i2c_bus_config = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = ESP_I2C_PORT,
        .scl_io_num = ESP_I2C_SCL,
        .sda_io_num = ESP_I2C_SDA,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };

    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_bus_config, &tool_bus_handle));
    return 0;
}

void i2cDetect(void)
{
    uint8_t address;
    printf("     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\r\n");
    for (int i = 0; i < 128; i += 16) {
        printf("%02x: ", i);
        for (int j = 0; j < 16; j++) {
            fflush(stdout);
            address = i + j;
            esp_err_t ret = i2c_master_probe(tool_bus_handle, address, I2C_TOOL_TIMEOUT_VALUE_MS);
            if (ret == ESP_OK) {
                printf("%02x ", address);
            } else if (ret == ESP_ERR_TIMEOUT) {
                printf("UU ");
            } else {
                printf("-- ");
            }
        }
        printf("\r\n");
    }
}