#include <string.h>
#include "logCmos.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_log.h"
#include "esp_timer.h"

static const char *TAG = "ERROR_STORE";
static const char *NVS_NAMESPACE = "err_storage";
static const char *NVS_KEY_LOGS = "logs";
static const char *NVS_KEY_INDEX = "head_idx";

typedef struct {
    uint32_t head;
    uint32_t count;
    error_log_entry_t entries[MAX_ERROR_LOGS];
} error_storage_data_t;

esp_err_t error_store_init(void) {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    return ret;
}

esp_err_t error_store_write(esp_err_t err_code, const char *message) {
    nvs_handle_t handle;
    esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READWRITE, &handle);
    if (err != ESP_OK) return err;

    error_storage_data_t data = {0};
    size_t required_size = sizeof(error_storage_data_t);

    // Lecture de l'état actuel s'il existe
    err = nvs_get_blob(handle, NVS_KEY_LOGS, &data, &required_size);
    if (err == ESP_ERR_NVS_NOT_FOUND) {
        data.head = 0;
        data.count = 0;
    } else if (err != ESP_OK) {
        nvs_close(handle);
        return err;
    }

    // Préparation de la nouvelle entrée
    error_log_entry_t *entry = &data.entries[data.head];
    entry->timestamp = (uint32_t)(esp_timer_get_time() / 1000);
    entry->err_code = err_code;
    
    memset(entry->message, 0, ERROR_MSG_SIZE);
    if (message) {
        strncpy(entry->message, message, ERROR_MSG_SIZE - 1);
    }

    // Mise à jour de l'index circulaire
    data.head = (data.head + 1) % MAX_ERROR_LOGS;
    if (data.count < MAX_ERROR_LOGS) {
        data.count++;
    }

    // Sauvegarde dans la NVS
    err = nvs_set_blob(handle, NVS_KEY_LOGS, &data, sizeof(error_storage_data_t));
    if (err == ESP_OK) {
        err = nvs_commit(handle);
    }

    nvs_close(handle);
    return err;
}

esp_err_t error_store_read_all(error_log_entry_t *logs, size_t *count) {
    if (!logs || !count) return ESP_ERR_INVALID_ARG;

    nvs_handle_t handle;
    esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READONLY, &handle);
    if (err != ESP_OK) {
        *count = 0;
        return err;
    }

    error_storage_data_t data = {0};
    size_t required_size = sizeof(error_storage_data_t);
    err = nvs_get_blob(handle, NVS_KEY_LOGS, &data, &required_size);
    nvs_close(handle);

    if (err != ESP_OK) {
        *count = 0;
        return err;
    }

    *count = data.count;
    
    // Restitution dans l'ordre chronologique (du plus ancien au plus récent)
    uint32_t start_idx = (data.count < MAX_ERROR_LOGS) ? 0 : data.head;
    for (size_t i = 0; i < data.count; i++) {
        uint32_t idx = (start_idx + i) % MAX_ERROR_LOGS;
        logs[i] = data.entries[idx];
    }

    return ESP_OK;
}

esp_err_t error_store_clear(void) {
    nvs_handle_t handle;
    esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READWRITE, &handle);
    if (err != ESP_OK) return err;

    err = nvs_erase_key(handle, NVS_KEY_LOGS);
    if (err == ESP_OK) {
        err = nvs_commit(handle);
    }

    nvs_close(handle);
    return err;
}