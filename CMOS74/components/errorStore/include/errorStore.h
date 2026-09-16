#ifndef ERROR_STORE_H
#define ERROR_STORE_H

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"

#define MAX_ERROR_LOGS 10
#define ERROR_MSG_SIZE 32

typedef struct {
    uint32_t timestamp;           // Temps système en ms (esp_log_timestamp)
    esp_err_t err_code;          // Code d'erreur ESP-IDF
    char message[ERROR_MSG_SIZE]; // Message court ou contexte
} error_log_entry_t;

/**
 * @brief Initialise le module de stockage et la NVS.
 */
esp_err_t error_store_init(void);

/**
 * @brief Enregistre une nouvelle erreur dans la NVS (mode tampon circulaire).
 */
esp_err_t error_store_write(esp_err_t err_code, const char *message);

/**
 * @brief Récupère l'ensemble des erreurs enregistrées.
 * @param logs Tableau de destination (taille minimale : MAX_ERROR_LOGS)
 * @param count Pointeur vers le nombre d'erreurs réellement lues
 */
esp_err_t error_store_read_all(error_log_entry_t *logs, size_t *count);

/**
 * @brief Efface toutes les erreurs stockées.
 */
esp_err_t error_store_clear(void);

#endif // ERROR_STORE_H