idf_component_register(SRCS "eepromTools.c" "eepromInterface.c" "eepromInterfaceDescriptor.c" "../charUtils/charUtils.c" "../uartCommand/uartCommand.c"
                        INCLUDE_DIRS "include" 
                        "../charUtils/include" 
                        "../uartCommand/include"
                        PRIV_REQUIRES fatfs esp_driver_i2c driver console esp_event
                        )