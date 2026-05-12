idf_component_register(SRCS "uartUtils.c"
                        INCLUDE_DIRS "include" 
                        "../charUtils/include" 
                        "../uartCommand/include"
                        "$ENV{IDF_PATH}/components/esp_event/include")
