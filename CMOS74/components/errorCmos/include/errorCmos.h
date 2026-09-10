/* ******************** 
Fonctionnalités clés
*********************
Fonctionnalité	        Description
error_log()	            Log une erreur depuis une tâche (thread-safe).
error_log_from_isr()	Log une erreur depuis une ISR (compatible avec les contextes interrupt).
error_get_last_log()	Récupère le dernier log enregistré.
error_print_last_log()	Affiche le dernier log (via UART, JTAG, etc.).
error_clear_buffer()	Vide le buffer de logs.
Buffer circulaire	    Gère les logs de manière efficace (pas de fuite mémoire).
Mutex	                Garantit l'accès thread-safe au buffer.
*/

#ifndef ERROR_CMOS_H
#define ERROR_CMOS_H

#include <stdint.h>
#include <string.h>

#include "esp_err.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


// Base offset pour ton composant personnalisé (Bit 17 activé + offset composant)
#define MY_APP_ERR_BASE             0x20000
#define MY_SENSOR_ERR_BASE          (MY_APP_ERR_BASE + 0x1000)

// Définition des erreurs spécifiques
#define ESP_ERR_SENSOR_TIMEOUT      (MY_SENSOR_ERR_BASE + 1) // 0x21001
#define ESP_ERR_SENSOR_INVALID_READ (MY_SENSOR_ERR_BASE + 2) // 0x21002
#define ESP_ERR_SENSOR_UNCALIBRATED (MY_SENSOR_ERR_BASE + 3) // 0x21003




/* --- Configuration --- */
#define ERROR_LOG_BUFFER_SIZE    256     ///< Taille du buffer de log (en octets).
#define ERROR_MAX_CODES          1000      ///< Nombre maximal de codes d'erreur.
#define ERROR_ENABLE_LOGGING     1       ///< Activer/désactiver le logging.

/* --- Types d'erreurs --- */
typedef enum {
    ERR_SUCCESS = 0,                    ///< Succès.
    ERR_MEMORY_ALLOCATION_FAILED,       ///< Échec d'allocation mémoire.
    ERR_STACK_OVERFLOW,                 ///< Dépassement de pile.
    ERR_TASK_CREATION_FAILED,           ///< Échec de création de tâche.
    ERR_QUEUE_CREATION_FAILED,          ///< Échec de création de file.
    ERR_SEMAPHORE_CREATION_FAILED,      ///< Échec de création de sémaphore.
    ERR_TIMER_CREATION_FAILED,          ///< Échec de création de timer.
    ERR_INVALID_PARAMETER,              ///< Paramètre invalide.
    ERR_HARD_FAULT,                     ///< Erreur matérielle (Hard Fault).
    ERR_UNKNOWN,                        ///< Erreur inconnue.
    
    ERR_USER_DEFINED_START = 0x100,     ///< Début des codes utilisateur.
    ERR_COMMAND_INVALID,                ///< Commande inconnu
    ERR_SEPARATOR_MISS,                 ///< Manque séparateur

    ERR_LED_CPU = 0x1000,                ///< Début des codes Cpu Led.
v
} ErrorCode_t;

/* --- Structure d'un log d'erreur --- */
typedef struct {
    ErrorCode_t code;                    ///< Code de l'erreur.
    const char *message;                 ///< Message descriptif.
    TickType_t timestamp;                ///< Timestamp (en ticks FreeRTOS).
    TaskHandle_t task;                   ///< Tâche concernée (NULL si globale).
} ErrorLog_t;

/* --- Buffer de logs --- */
typedef struct {
    ErrorLog_t logs[ERROR_LOG_BUFFER_SIZE];
    uint16_t head;                       ///< Index d'écriture.
    uint16_t count;                      ///< Nombre de logs enregistrés.
    SemaphoreHandle_t mutex;             ///< Mutex pour accès thread-safe.
} ErrorLogBuffer_t;

/* --- Prototypes --- */
void error_init(void);
void error_log(ErrorCode_t code, const char *message, TaskHandle_t task);
void error_log_from_isr(ErrorCode_t code, const char *message, TaskHandle_t task);
const ErrorLog_t *error_get_last_log(void);
void error_print_last_log(void);
void error_clear_buffer(void);

#endif