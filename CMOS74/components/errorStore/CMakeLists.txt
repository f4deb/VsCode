idf_component_register(SRCS "errorSroreInterfaceDescriptor.c" "errorStoreInterface.c" "errorStore.c"
                    INCLUDE_DIRS "include"
                PRIV_REQUIRES esp_timer nvs_flash esp_event
                )