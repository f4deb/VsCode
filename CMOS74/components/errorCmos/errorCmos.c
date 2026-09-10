#include "errorCmos.h"

#include <stdarg.h>
#include <stdio.h>

#include "esp_log.h"





/* --- Variables globales --- */
static ErrorLogBuffer_t error_buffer = {0};

// Variable pour conserver le pointeur vers la fonction système d'origine
static vprintf_like_t s_previous_log_func = NULL;

int my_custom_log_vprintf(const char *fmt, va_list args) {
    // 1. (Optionnel) Traitement personnalisé : envoyer sur réseau, fichier, etc.
    // Exemple : vprintf_to_sd_card(fmt, args);

    // 2. Transmettre également au gestionnaire d'origine (UART) si souhaité
    if (s_previous_log_func != NULL) {
        return s_previous_log_func(fmt, args);
    }
    
    return 0;
}


// Convertisseur personnalisé
const char* custom_err_to_name(esp_err_t code) {
    switch (code) {
        case ESP_ERR_SENSOR_TIMEOUT:      return "ESP_ERR_SENSOR_TIMEOUT";
        case ESP_ERR_SENSOR_INVALID_READ: return "ESP_ERR_SENSOR_INVALID_READ";
        case ESP_ERR_SENSOR_UNCALIBRATED: return "ESP_ERR_SENSOR_UNCALIBRATED";
        default:                          return NULL; // Laisse esp_err_to_name gérer les autres
    }
}








/* --- Initialisation --- */
void error_init(void) {

// Enregistrement de la nouvelle fonction et récupération de l'ancienne
    s_previous_log_func = esp_log_set_vprintf(my_custom_log_vprintf);


    error_buffer.mutex = xSemaphoreCreateMutex();
    if (error_buffer.mutex == NULL) {
        // Impossible de créer le mutex : erreur critique !
        while(1); // Boucle infinie pour éviter un comportement indéfini.
    }
    error_clear_buffer();
}

/* --- Log d'erreur (contexte tâche) --- */
void error_log(ErrorCode_t code, const char *message, TaskHandle_t task) {
    if (ERROR_ENABLE_LOGGING == 0) return;

    xSemaphoreTake(error_buffer.mutex, portMAX_DELAY);

    // Vérifier si le buffer est plein
    if (error_buffer.count >= ERROR_LOG_BUFFER_SIZE) {
        // Buffer plein : écraser le plus ancien log
        error_buffer.head = (error_buffer.head + 1) % ERROR_LOG_BUFFER_SIZE;
    } else {
        error_buffer.count++;
    }

    // Écrire le nouveau log
    ErrorLog_t *log = &error_buffer.logs[error_buffer.head];
    log->code = code;
    log->message = message;
    log->timestamp = xTaskGetTickCount();
    log->task = task;

    xSemaphoreGive(error_buffer.mutex);
}

/* --- Log d'erreur (contexte ISR) --- */
void error_log_from_isr(ErrorCode_t code, const char *message, TaskHandle_t task) {
    if (ERROR_ENABLE_LOGGING == 0) return;

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreTakeFromISR(error_buffer.mutex, &xHigherPriorityTaskWoken);

    // Vérifier si le buffer est plein
    if (error_buffer.count >= ERROR_LOG_BUFFER_SIZE) {
        error_buffer.head = (error_buffer.head + 1) % ERROR_LOG_BUFFER_SIZE;
    } else {
        error_buffer.count++;
    }

    // Écrire le nouveau log
    ErrorLog_t *log = &error_buffer.logs[error_buffer.head];
    log->code = code;
    log->message = message;
    log->timestamp = xTaskGetTickCountFromISR();
    log->task = task;

    xSemaphoreGiveFromISR(error_buffer.mutex, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

/* --- Récupérer le dernier log --- */
const ErrorLog_t *error_get_last_log(void) {
    if (error_buffer.count == 0) return NULL;

    uint16_t last_index = (error_buffer.head - error_buffer.count + ERROR_LOG_BUFFER_SIZE) % ERROR_LOG_BUFFER_SIZE;
    return &error_buffer.logs[last_index];
}

/* --- Afficher le dernier log (via UART ou autre) --- */
void error_print_last_log(void) {
    const ErrorLog_t *log = error_get_last_log();
    if (log == NULL) {
        printf("Aucun log d'erreur disponible.\n");
        return;
    }

    const char *task_name = (log->task != NULL) ? pcTaskGetName(log->task) : "N/A";

    printf("[ERROR] Code: %d, Message: %s, Tâche: %s, Timestamp: ???\n",
           log->code,
           log->message,
           task_name);
}

/* --- Vider le buffer de logs --- */
void error_clear_buffer(void) {
    xSemaphoreTake(error_buffer.mutex, portMAX_DELAY);
    error_buffer.head = 0;
    error_buffer.count = 0;
    xSemaphoreGive(error_buffer.mutex);
}