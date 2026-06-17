idf_component_register(SRCS "cpuLedInterfaceDescriptor.c" "cpuLedInterface.c" "cpuLed.c" "../charUtils/charUtils.c" "../uartCommand/uartCommand.c"
                        INCLUDE_DIRS "include" 
                        "../charUtils/include" 
                        "../uartCommand/include"
                        PRIV_REQUIRES fatfs esp_driver_i2c driver esp_driver_gpio esp_event
                        )