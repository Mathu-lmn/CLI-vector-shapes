/**
 * @file area.c
 * @author Mathurin Lemoine / Chengfeng Ding
 * @brief Fichier contenant les fonctions de gestion de zone de dessin
 * @version 1.0
 * @date 03/06/2023
 */

#include "area.h"

Area * create_area(unsigned int width, unsigned int height) {
    Area * area = malloc(sizeof(Area));
    area->width = width;
    area->height = height;
    area->nb_shape = 0;
    // mat est un tableau de BOOL * de taille width
    area->mat = malloc(sizeof(BOOL *) * width);
    for (int i = 0; i < width; ++i) {
        // pour chaque ligne de mat, on alloue un tableau de BOOL de taille height
        area->mat[i] = calloc(height,sizeof(BOOL));
    }
    return area;
}

void add_shape_to_area(Area *area, Shape *shape) {
    if (area->nb_shape >= SHAPE_MAX) {
        printf("Erreur : nombre maximum de formes atteint\n");
        return;
    }
    area->shapes[area->nb_shape] = shape;
    area->nb_shape++;
}

void clear_area(Area *area) {
    // reset de tous les pixels
    for (int i = 0; i < area->width; i++) {
        for (int j = 0; j < area->height; j++) {
            area->mat[i][j] = 0;
        }
    }
}

void erase_area(Area *area) {
    // reset de toutes les formes
    for (int i = 0; i < area->nb_shape; ++i) {
        delete_shape(area->shapes[i]);
    }
    area->nb_shape = 0;
}

void delete_area(Area *area) {
    // libération de la mémoire
    erase_area(area);
    free(area);
}

void draw_area(Area *area) {
    // reset de tous les pixels
    clear_area(area);
    // pour chaque forme
    for (int j = 0; j < area->nb_shape; j++) {
        int nb_pixels = 0;
        Pixel **res = create_shape_to_pixel(area->shapes[j], &nb_pixels);
        // pour chaque pixel de la forme
        for (int i = 0; i < nb_pixels; i++) {
            // on récupère les coordonnées du pixel
            int px = res[i]->px;
            int py = res[i]->py;
            // on met à jour la matrice si le pixel est dans la zone
            if (px >= 0 && px < area->width && py >= 0 && py < area->height){
                area->mat[px][py] = 1;
            }
        }
    }
}

void print_area(Area *area) {
    // affichage de la matrice
    for (int i = 0; i < area->width; i++) {
        for (int j = 0; j < area->height; j++) {
            printf(" %c ", area->mat[i][j] ? '#' : '.');
        }
        printf("\n");
    }
}

// DOCUMENTATION

/**
 * @struct Area
 * @brief Structure représentant une zone de dessin
 */

/**
 * @typedef BOOL
 * @brief Type booléen représentant vrai (1) ou faux (0)
 */

/**
 * @struct Area
 * @brief Structure représentant une zone de dessin
 * @var Area::width
 * La largeur de la zone de dessin
 * @var Area::height
 * La hauteur de la zone de dessin
 * @var Area::nb_shape
 * Le nombre de formes dans la zone
 * @var Area::mat
 * Matrice représentant les pixels de la zone
 * @var Area::shapes
 * Tableau des formes dans la zone
 */

/**
 * @typedef Area
 * @brief Alias pour le type `struct Area`
 */

/**
 * @typedef Shape
 * @brief Alias pour le type `struct Shape`
 */

/**
 * @typedef Pixel
 * @brief Alias pour le type `struct Pixel`
 */

/**
 * @fn Area *create_area(unsigned int width, unsigned int height)
 * @brief Crée une nouvelle zone de dessin.
 * @param width La largeur de la zone de dessin
 * @param height La hauteur de la zone de dessin
 * @return Un pointeur vers la zone de dessin créée
 */

/**
 * @fn void add_shape_to_area(Area *area, Shape *shape)
 * @brief Ajoute une forme à la zone de dessin.
 * @param area La zone de dessin
 * @param shape La forme à ajouter
 */

/**
 * @fn void clear_area(Area *area)
 * @brief Efface tous les pixels de la zone de dessin.
 * @param area La zone de dessin
 */

/**
 * @fn void erase_area(Area *area)
 * @brief Efface toutes les formes de la zone de dessin.
 * @param area La zone de dessin
 */

/**
 * @fn void delete_area(Area *area)
 * @brief Supprime une zone de dessin et libère la mémoire associée.
 * @param area La zone de dessin à supprimer
 */

/**
 * @fn void draw_area(Area *area)
 * @brief Dessine les formes présentes dans la zone de dessin.
 * @param area La zone de dessin
 */

/**
 * @fn void print_area(Area *area)
 * @brief Affiche la zone de dessin.
 * @param area La zone de dessin à afficher
 */