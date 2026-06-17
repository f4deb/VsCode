idf_component_register(SRCS "uartUtils.c"
                        INCLUDE_DIRS "include" 
                        "../charUtils/include" 
                        "../uartCommand/include"
                        REQUIRES esp_driver_uart driver esp_event
                        )