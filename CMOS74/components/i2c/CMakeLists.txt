idf_component_register(SRCS "i2cInterfaceDescriptor.c" "i2cTools.c" "i2cInterface.c" "../charUtils/charUtils.c" "../uartCommand/uartCommand.c"
                        INCLUDE_DIRS "include" 
                        "../charUtils/include" 
                        "../uartCommand/include"
                        "../eeprom/include"
                        PRIV_REQUIRES fatfs esp_driver_i2c driver console esp_event
                        )