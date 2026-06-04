idf_component_register(SRCS "sevenSegmentsInterfaceDescriptor.c" "sevenSegmentsInterface.c" "sevenSegments.c" "../charUtils/charUtils.c" "../uartCommand/uartCommand.c"
                        INCLUDE_DIRS "include" 
                        "../charUtils/include" 
                        "../uartCommand/include"
                        "../interface/include"
                        "$ENV{IDF_PATH}/components/esp_event/include"
                        "$ENV{IDF_PATH}/components/esp_driver_gpio/include"
                        )