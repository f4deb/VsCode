#ifndef ERROR_STORE_H
#define ERROR_STORE_H

#include <stdint.h>
#include <stddef.h>
#include "esp_err.h"

#define MAX_ERROR_LOGS 20
#define ERROR_MSG_SIZE 64

typedef struct {
    uint32_t timestamp;
    esp_err_t err_code;
    char message[ERROR_MSG_SIZE];
} error_log_entry_t;

/**
 * @brief Initialise la mémoire NVS et le mutex de synchronisation.
 */
esp_err_t error_store_init(void);

/**
 * @brief Écrit un nouveau log dans le buffer circulaire NVS.
 */
esp_err_t error_store_write(esp_err_t err_code, const char *message);

/**
 * @brief Lit tous les logs enregistrés du plus ancien au plus récent.
 */
esp_err_t error_store_read_all(error_log_entry_t *logs, size_t *count);

/**
 * @brief Efface l'ensemble des logs stockés dans la NVS.
 */
esp_err_t error_store_clear(void);

#endif // ERROR_STORE_H