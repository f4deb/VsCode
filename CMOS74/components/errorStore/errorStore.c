#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_log.h"
#include "esp_timer.h"

#include "errorStore.h"

static const char *TAG = "ERROR_STORE";
static const char *NVS_NAMESPACE = "err_storage";
static const char *NVS_KEY_LOGS = "logs";

typedef struct {
    uint32_t head;
    uint32_t count;
    error_log_entry_t entries[MAX_ERROR_LOGS];
} error_storage_data_t;

static SemaphoreHandle_t s_nvs_mutex = NULL;

esp_err_t error_store_init(void) {
    if (s_nvs_mutex == NULL) {
        s_nvs_mutex = xSemaphoreCreateMutex();
        if (s_nvs_mutex == NULL) {
            ESP_LOGE(TAG, "Échec de création du mutex NVS");
            return ESP_ERR_NO_MEM;
        }
    }

    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_LOGW(TAG, "Effacement de la partition NVS suite à une erreur d'initialisation...");
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    return ret;
}

esp_err_t error_store_write(esp_err_t err_code, const char *message) {
    if (s_nvs_mutex == NULL) return ESP_ERR_INVALID_STATE;

    if (xSemaphoreTake(s_nvs_mutex, pdMS_TO_TICKS(1000)) != pdTRUE) {
        return ESP_ERR_TIMEOUT;
    }

    nvs_handle_t handle;
    esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READWRITE, &handle);
    if (err != ESP_OK) {
        xSemaphoreGive(s_nvs_mutex);
        return err;
    }

    // Dynamic allocation off the stack to prevent stack overflow
    error_storage_data_t *data = heap_caps_malloc(sizeof(error_storage_data_t), MALLOC_CAP_8BIT);
    if (!data) {
        nvs_close(handle);
        xSemaphoreGive(s_nvs_mutex);
        return ESP_ERR_NO_MEM;
    }
    memset(data, 0, sizeof(error_storage_data_t));

    size_t required_size = sizeof(error_storage_data_t);
    err = nvs_get_blob(handle, NVS_KEY_LOGS, data, &required_size);
    if (err == ESP_ERR_NVS_NOT_FOUND) {
        data->head = 0;
        data->count = 0;
        err = ESP_OK;
    } else if (err != ESP_OK) {
        free(data);
        nvs_close(handle);
        xSemaphoreGive(s_nvs_mutex);
        return err;
    }

    error_log_entry_t *entry = &data->entries[data->head];
    entry->timestamp = (uint32_t)(esp_timer_get_time() / 1000);
    entry->err_code = err_code;
    
    memset(entry->message, 0, ERROR_MSG_SIZE);
    if (message) {
        strncpy(entry->message, message, ERROR_MSG_SIZE - 1);
    }

    data->head = (data->head + 1) % MAX_ERROR_LOGS;
    if (data->count < MAX_ERROR_LOGS) {
        data->count++;
    }

    err = nvs_set_blob(handle, NVS_KEY_LOGS, data, sizeof(error_storage_data_t));
    if (err == ESP_OK) {
        err = nvs_commit(handle);
    }

    free(data);
    nvs_close(handle);
    xSemaphoreGive(s_nvs_mutex);
    return err;
}

esp_err_t error_store_read_all(error_log_entry_t *logs, size_t *count) {
    if (!logs || !count || s_nvs_mutex == NULL) return ESP_ERR_INVALID_ARG;

    if (xSemaphoreTake(s_nvs_mutex, pdMS_TO_TICKS(1000)) != pdTRUE) {
        *count = 0;
        return ESP_ERR_TIMEOUT;
    }

    nvs_handle_t handle;
    esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READONLY, &handle);
    if (err != ESP_OK) {
        *count = 0;
        xSemaphoreGive(s_nvs_mutex);
        return err;
    }

    error_storage_data_t *data = heap_caps_malloc(sizeof(error_storage_data_t), MALLOC_CAP_8BIT);
    if (!data) {
        *count = 0;
        nvs_close(handle);
        xSemaphoreGive(s_nvs_mutex);
        return ESP_ERR_NO_MEM;
    }
    memset(data, 0, sizeof(error_storage_data_t));

    size_t required_size = sizeof(error_storage_data_t);
    err = nvs_get_blob(handle, NVS_KEY_LOGS, data, &required_size);
    nvs_close(handle);

    if (err != ESP_OK) {
        *count = 0;
        free(data);
        xSemaphoreGive(s_nvs_mutex);
        return err;
    }

    *count = data->count;
    
    uint32_t start_idx = (data->count < MAX_ERROR_LOGS) ? 0 : data->head;
    for (size_t i = 0; i < data->count; i++) {
        uint32_t idx = (start_idx + i) % MAX_ERROR_LOGS;
        logs[i] = data->entries[idx];
    }

    free(data);
    xSemaphoreGive(s_nvs_mutex);
    return ESP_OK;
}

esp_err_t error_store_clear(void) {
    if (s_nvs_mutex == NULL) return ESP_ERR_INVALID_STATE;

    if (xSemaphoreTake(s_nvs_mutex, pdMS_TO_TICKS(1000)) != pdTRUE) {
        return ESP_ERR_TIMEOUT;
    }

    nvs_handle_t handle;
    esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READWRITE, &handle);
    if (err != ESP_OK) {
        xSemaphoreGive(s_nvs_mutex);
        return err;
    }

    err = nvs_erase_key(handle, NVS_KEY_LOGS);
    if (err == ESP_OK) {
        err = nvs_commit(handle);
    }

    nvs_close(handle);
    xSemaphoreGive(s_nvs_mutex);
    return err;
}