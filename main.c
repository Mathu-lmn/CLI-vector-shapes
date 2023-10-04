/**
 * @file main.c
 * @author Mathurin Lemoine / Chengfeng Ding
 * @brief Fichier contenant la fonction main
 * @version 1.0
 * @date 03/06/2023
 */

#include "main.h"

int main() {
    printf("Bienvenue dans le projet de C !\n");
    Command *cmd = create_commande();
    do {
        printf(">");
        read_from_stdin(cmd);
    } while (read_exec_command(cmd) != 0);

    return 0;
}

// DOCUMENTATION

/**
 * @fn int main()
 * @brief Fonction principale du programme.
 * @return La valeur de sortie du programme
 */