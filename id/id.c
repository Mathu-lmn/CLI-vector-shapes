/**
 * @file id.c
 * @author Mathurin Lemoine / Chengfeng Ding
 * @brief Fichier contenant les fonctions de gestion des ids des formes
 * @version 1.0
 * @date 03/06/2023
 */

#include "id.h"

unsigned int get_next_id() {
    return global_id++;
}

// DOCUMENTATION

/**
 * @var global_id
 * @brief Variable globale représentant l'identifiant global des formes
 */

/**
 * @fn unsigned int get_next_id()
 * @brief Obtient le prochain identifiant disponible.
 * @return Le prochain identifiant disponible
 */