#ifndef INTERFACE_H
#define INTERFACE_H

#include "esp_err.h"

// Plage 0x90100 pour le moteur
#define ESP_ERR_INTERFACE_BASE          0x90100
#define ESP_ERR_NO_SEPARATOR            (ESP_ERR_INTERFACE_BASE + 1)


#define INTERFACE_TASK_STACK_SIZE   3072


#define INTERFACE_DEBUG 0

#define INTERFACE_HEADER "jk+"
#define INTERFACE_HEADER_SIZE 3

// Fonction pour traduire l'erreur en chaîne de caractères
const char* interface_err_to_name(esp_err_t err);

void interface_task(void *arg);

#endif