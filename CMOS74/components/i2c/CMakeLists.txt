idf_component_register(SRCS "i2cInterfaceDescriptor.c" "i2cTools.c" "i2cInterface.c" "../charUtils/charUtils.c" "../uartCommand/uartCommand.c"
                        INCLUDE_DIRS "include" 
                        "../charUtils/include" 
                        "../uartCommand/include"
                        "../interface/include"
                        "../cmos/include"
                        "$ENV{IDF_PATH}/components/esp_event/include"
                        "$ENV{IDF_PATH}/components/console"
                        "$ENV{IDF_PATH}/components/esp_driver_gpio/include"
                        PRIV_REQUIRES fatfs esp_driver_i2c driver
                        )