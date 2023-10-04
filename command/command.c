/**
 * @file command.c
 * @author Mathurin Lemoine / Chengfeng Ding
 * @brief Fichier contenant les fonctions de gestion de commandes utilisateur
 * @version 1.0
 * @date 03/06/2023
 */

#include "command.h"

Area *current_area = NULL;

Command *create_commande() {
    Command *cmd = malloc(sizeof(Command));
    // Initialiser à 0 les paramètres
    cmd->int_size = 0;
    cmd->str_size = 0;
    // Initialiser les paramètres pour éviter les valeurs aléatoires
    for (int i = 0; i < 10; ++i) {
        cmd->int_params[i] = 0;
        cmd->str_params[i] = NULL;
    }

    if (current_area == NULL) {
        current_area = create_area(30, 30);
    }
    return cmd;
}


void add_str_param(Command *cmd, char *p) {
    cmd->str_params[cmd->str_size] = p;
    cmd->str_size++;
}

void add_int_param(Command *cmd, int p) {
    cmd->int_params[cmd->int_size] = p;
    cmd->int_size++;
}

void free_cmd(Command *cmd) {
    for (int i = 0; i < cmd->str_size; ++i) {
        free(cmd->str_params[i]);
    }
    free(cmd);
}

int read_exec_command(Command *cmd) {
    if (strcmp(cmd->name, "clear") == 0) {
        // clear
        // clear the screen
        printf("\e[1;1H\e[2J");
    } else if (strcmp(cmd->name, "exit") == 0) {
        // exit
        // exit the program
        return 0;
    } else if (strcmp(cmd->name, "point") == 0) {
        // point <px> <py>
        // ajouter un point à area
        if (cmd->int_size != 2) {
            printf("Error: la commande point requiert 2 parametres\n");
            return 1;
        }
        Shape *p = create_point_shape(cmd->int_params[0], cmd->int_params[1]);
        add_shape_to_area(current_area, p);
    } else if (strcmp(cmd->name, "line") == 0) {
        // line <px1> <py1> <px2> <py2>
        // add a shape to the area
        if (cmd->int_size != 4) {
            printf("Error: la commande line requiert 4 parametres\n");
            return 1;
        }
        Shape *p = create_line_shape(cmd->int_params[0], cmd->int_params[1], cmd->int_params[2], cmd->int_params[3]);
        add_shape_to_area(current_area, p);
    } else if (strcmp(cmd->name, "circle") == 0) {
        // circle <px> <py> <r>
        // add a shape to the area
        if (cmd->int_size != 3) {
            printf("Error: la commande circle requiert 3 parametres\n");
            return 1;
        }
        Shape *p = create_circle_shape(cmd->int_params[0], cmd->int_params[1], cmd->int_params[2]);
        add_shape_to_area(current_area, p);
    } else if (strcmp(cmd->name, "square") == 0) {
        // square <px> <py> <side>
        // add a shape to the area
        if (cmd->int_size != 3) {
            printf("Error: la commande square requiert 3 parametres\n");
            return 1;
        }
        Shape *p = create_square_shape(cmd->int_params[0], cmd->int_params[1], cmd->int_params[2]);
        add_shape_to_area(current_area, p);
    } else if (strcmp(cmd->name, "rectangle") == 0) {
        // rectangle <px> <py> <width> <height>
        // add a shape to the area
        if (cmd->int_size != 4) {
            printf("Error: la commande rectangle requiert 4 parametres\n");
            return 1;
        }
        Shape *p = create_rectangle_shape(cmd->int_params[0], cmd->int_params[1], cmd->int_params[2],
                                          cmd->int_params[3]);
        add_shape_to_area(current_area, p);
    } else if (strcmp(cmd->name, "polygon") == 0) {
        // polygon <px1> <py1> <px2> <py2> ... <pxn> <pyn>
        // add a shape to the area
        if (cmd->int_size % 2 != 0) {
            printf("Error: vous devez donner un nombre pair de parametres\n");
            return 1;
        }
        Shape *p = create_polygon_shape(cmd->int_params, cmd->int_size);
        add_shape_to_area(current_area, p);
    } else if (strcmp(cmd->name, "plot") == 0) {
        // plot
        // plot the area
        draw_area(current_area);
        print_area(current_area);
    } else if (strcmp(cmd->name, "list") == 0) {
        // list
        // list all the shapes
        for (int i = 0; i < current_area->nb_shape; ++i) {
            print_shape(current_area->shapes[i]);
            printf("\n");
        }
    } else if (strcmp(cmd->name, "delete") == 0) {
        // delete <id>
        // delete a shape
        if (cmd->int_size != 1) {
            printf("Error: la commande delete requiert 1 parametre\n");
            return 1;
        }
        for (int i = 0; i < current_area->nb_shape; ++i) {
            if (current_area->shapes[i]->id == cmd->int_params[0]) {
                delete_shape(current_area->shapes[i]);
                // décaler les autres shapes
                for (int j = i; j < current_area->nb_shape - 1; ++j) {
                    current_area->shapes[j] = current_area->shapes[j + 1];
                }
                current_area->nb_shape--;
                return 1;
            }
        }
    } else if (strcmp(cmd->name, "erase") == 0) {
        // erase all the shapes
        erase_area(current_area);
        printf("\e[1;1H\e[2J");
    } else if (strcmp(cmd->name, "help") == 0) {
        // help
        // display the help (all commands with their parameters)
        printf("clear\t\t\t\t\t\t\t Nettoie la console\n");
        printf("exit\t\t\t\t\t\t\t Quitte le programme\n");
        printf("point <px> <py>\t\t\t\t\t\t Ajouter un point a la zone\n");
        printf("line <px1> <py1> <px2> <py2>\t\t\t\t Ajouter une ligne a la zone\n");
        printf("circle <px> <py> <r>\t\t\t\t\t Ajouter un cercle a la zone\n");
        printf("square <px> <py> <side>\t\t\t\t\t Ajouter un carre a la zone\n");
        printf("rectangle <px> <py> <width> <height>\t\t\t Ajouter un rectangle a la zone\n");
        printf("polygon <px1> <py1> <px2> <py2> ... <pxn> <pyn>\t\t Ajouter un polygone a la zone\n");
        printf("plot\t\t\t\t\t\t\t Dessine la zone\n");
        printf("list\t\t\t\t\t\t\t Liste des formes dans la zone\n");
        printf("delete <id>\t\t\t\t\t\t Supprime une forme\n");
        printf("erase\t\t\t\t\t\t\t Effacer toutes les formes\n");
        printf("help\t\t\t\t\t\t\t Montre les commandes\n");
    } else {
        printf("Commande inconnue : %s\n", cmd->name);
    }
    return 1;
}

void read_from_stdin(Command *cmd) {
    char *line = malloc(100 * sizeof(char));
    fgets(line, 100, stdin);
    int len = strlen(line);
    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';

    // clear the previous command
    cmd->int_size = 0;
    cmd->str_size = 0;
    for (int i = 0; i < 10; ++i) {
        cmd->int_params[i] = 0;
        cmd->str_params[i] = NULL;
    }
    // save the first word in cmd->name
    char *name = strtok(line, " ");
    if (name != NULL) {
        strcpy(cmd->name, name);
    } else {
        printf("Error: aucune commande donnée\n");
        return;
    }
    char *temp = strtok(NULL, " ");
    while (temp != NULL) {
        if (temp[0] >= '0' && temp[0] <= '9') {
            add_int_param(cmd, atoi(temp));
        } else {
            add_str_param(cmd, temp);
        }
        temp = strtok(NULL, " ");
    }
    free(line);
}


// DOCUMENTATION

/**
 * @var current_area
 * @brief Pointeur vers la zone courante
 */

/**
 * @struct Command
 * @brief Structure représentant une commande utilisateur
 * @var Command::name
 * Le nom de la commande
 * @var Command::int_params
 * Tableau des paramètres entiers
 * @var Command::int_size
 * Le nombre de paramètres entiers
 * @var Command::str_params
 * Tableau des paramètres de chaîne de caractères
 * @var Command::str_size
 * Le nombre de paramètres de chaîne de caractères
 */

/**
 * @typedef Command
 * @brief Alias pour le type `struct Command`
 */

/**
 * @fn Command *create_commande()
 * @brief Crée une nouvelle commande.
 * @return Un pointeur vers la commande créée
 */

/**
 * @fn void add_str_param(Command *cmd, char *p)
 * @brief Ajoute un paramètre de chaîne de caractères à une commande.
 * @param cmd La commande à laquelle ajouter le paramètre
 * @param p Le paramètre de chaîne de caractères à ajouter
 */

/**
 * @fn void add_int_param(Command *cmd, int p)
 * @brief Ajoute un paramètre entier à une commande.
 * @param cmd La commande à laquelle ajouter le paramètre
 * @param p Le paramètre entier à ajouter
 */

/**
 * @fn void free_cmd(Command *cmd)
 * @brief Libère la mémoire occupée par une commande.
 * @param cmd La commande à libérer
 */

/**
 * @fn int read_exec_command(Command *cmd)
 * @brief Lit et exécute une commande.
 * @param cmd La commande à lire et exécuter
 * @return 0 si la commande est une commande de sortie du programme, 1 sinon
 */

/**
 * @fn void read_from_stdin(Command *cmd)
 * @brief Lit une commande à partir de l'entrée standard.
 * @param cmd La commande à lire
 */
