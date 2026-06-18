idf_component_register(SRCS "i2cEeprom.c"
                    INCLUDE_DIRS "include"
                    REQUIRES esp_driver_uart driver
                    )