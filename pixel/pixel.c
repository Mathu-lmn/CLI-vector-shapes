/**
 * @file pixel.c
 * @author Mathurin Lemoine / Chengfeng Ding
 * @brief Fichier contenant les fonctions de gestion des pixels (visuels des formes)
 * @version 1.0
 * @date 03/06/2023
 */

#include "pixel.h"

Pixel *create_pixel(int px, int py) {
    Pixel *pixel = malloc(sizeof(Pixel));
    pixel->px = px;
    pixel->py = py;
    return pixel;
}

void delete_pixel(Pixel *pixel) {
    free(pixel);
}

void pixel_point(Shape *shape, Pixel ***pixel_tab, int *nb_pixels) {
    Point *pt = (Point *) shape->ptrShape;
    *pixel_tab = malloc(sizeof(Pixel *));
    *pixel_tab[0] = create_pixel(pt->pos_x, pt->pos_y);
    *nb_pixels = 1;
}

void pixel_line(Shape *line, Pixel ***pixel_tab, int *nb_pixels) {
    Line *l = line->ptrShape;
    int x1 = l->p1->pos_x;
    int y1 = l->p1->pos_y;
    int x2 = l->p2->pos_x;
    int y2 = l->p2->pos_y;
    int dx = abs(x2 - x1); // Utiliser la valeur absolue de dx pour gérer les points dans n'importe quel ordre
    int dy = abs(y2 - y1);
    int x = x1;
    int y = y1;
    int i;
    *nb_pixels = 0;
    // si aucun déplacement en x ou y, on a une ligne verticale ou horizontale
    if (dx == 0) {
        *pixel_tab = malloc(sizeof(Pixel *) * (dy + 1));
        // pour chaque itération, on crée un pixel et on l'ajoute au tableau, puis on incrémente y ainsi que le nombre de pixels
        if (y1 < y2) {
            for (i = 0; i <= dy; i++) {
                (*pixel_tab)[i] = create_pixel(x, y);
                y++;
                *nb_pixels += 1;
            }
        } else {
            for (i = 0; i <= dy; i++) {
                (*pixel_tab)[i] = create_pixel(x, y);
                y--;
                *nb_pixels += 1;
            }
        }
    } else if (dy == 0) {
        *pixel_tab = malloc(sizeof(Pixel *) * (dx + 1));
        // pour chaque itération, on crée un pixel et on l'ajoute au tableau, puis on incrémente x ainsi que le nombre de pixels
        if (x1 < x2) {
            for (i = 0; i <= dx; i++) {
                (*pixel_tab)[i] = create_pixel(x, y);
                x++;
                *nb_pixels += 1;
            }
        } else {
            for (i = 0; i <= dx; i++) {
                (*pixel_tab)[i] = create_pixel(x, y);
                x--;
                *nb_pixels += 1;
            }
        }
    } else {
        int step_x = (x1 < x2) ? 1 : -1;
        int step_y = (y1 < y2) ? 1 : -1;

        if (dx > dy) {
            *pixel_tab = malloc(sizeof(Pixel *) * (dx + 1));
            int error = dx / 2;
            for (i = 0; i <= dx; i++) {
                (*pixel_tab)[i] = create_pixel(x, y);
                x += step_x;
                error -= dy;
                if (error < 0) {
                    y += step_y;
                    error += dx;
                }
                *nb_pixels += 1;
            }
        } else {
            *pixel_tab = malloc(sizeof(Pixel *) * (dy + 1));
            int error = dy / 2;
            for (i = 0; i <= dy; i++) {
                (*pixel_tab)[i] = create_pixel(x, y);
                y += step_y;
                error -= dx;
                if (error < 0) {
                    x += step_x;
                    error += dy;
                }
                *nb_pixels += 1;
            }
        }
    }
}


void pixel_circle(Shape *shape, Pixel ***pixel_tab, int *nb_pixels) {
    Circle *c = (Circle *) shape->ptrShape;
    int x = 0;
    int y = c->radius;
    int d = c->radius - 1;
    *nb_pixels = 0;
    *pixel_tab = malloc(sizeof(Pixel *) * (2 * c->radius + 1) * 8);
    while (y >= x) {
        (*pixel_tab)[(*nb_pixels)++] = create_pixel(c->center->pos_x + x, c->center->pos_y + y);
        (*pixel_tab)[(*nb_pixels)++] = create_pixel(c->center->pos_x + y, c->center->pos_y + x);
        (*pixel_tab)[(*nb_pixels)++] = create_pixel(c->center->pos_x - x, c->center->pos_y + y);
        (*pixel_tab)[(*nb_pixels)++] = create_pixel(c->center->pos_x - y, c->center->pos_y + x);
        (*pixel_tab)[(*nb_pixels)++] = create_pixel(c->center->pos_x + x, c->center->pos_y - y);
        (*pixel_tab)[(*nb_pixels)++] = create_pixel(c->center->pos_x + y, c->center->pos_y - x);
        (*pixel_tab)[(*nb_pixels)++] = create_pixel(c->center->pos_x - x, c->center->pos_y - y);
        (*pixel_tab)[(*nb_pixels)++] = create_pixel(c->center->pos_x - y, c->center->pos_y - x);

        if (d >= 2 * x) {
            d = d - (2 * x + 1);
            x++;
        } else if (d < 2 * (c->radius - y)) {
            d = d + (2 * y - 1);
            y--;
        } else {
            d = d + (2 * (y - x - 1));
            y--;
            x++;
        }
    }
}

void pixel_square(Shape *square, Pixel ***pixel_tab, int *nb_pixels) {
    Square *s = (Square *) square->ptrShape;
    int x = s->p->pos_x;
    int y = s->p->pos_y;
    int length = s->length;

    *pixel_tab = malloc(sizeof(Pixel *) * (length * 4));
    *nb_pixels = 0;

    Shape *line1 = create_line_shape(x, y, x + length - 1, y);
    int line_nb_pixels = 0;
    Pixel **line_pixels = NULL;
    pixel_line(line1, &line_pixels, &line_nb_pixels);
    for (int i = 0; i < line_nb_pixels; i++) {
        (*pixel_tab)[(*nb_pixels)++] = line_pixels[i];
    }
    free(line1);

    Shape *line2 = create_line_shape(x + length, y, x + length, y + length - 1);
    line_nb_pixels = 0;
    line_pixels = NULL;
    pixel_line(line2, &line_pixels, &line_nb_pixels);
    for (int i = 0; i < line_nb_pixels; i++) {
        (*pixel_tab)[(*nb_pixels)++] = line_pixels[i];
    }
    free(line2);

    Shape *line3 = create_line_shape(x + length, y + length, x + 1, y + length);
    line_nb_pixels = 0;
    line_pixels = NULL;
    pixel_line(line3, &line_pixels, &line_nb_pixels);
    for (int i = 0; i < line_nb_pixels; i++) {
        (*pixel_tab)[(*nb_pixels)++] = line_pixels[i];
    }
    free(line3);

    Shape *line4 = create_line_shape(x, y + length, x, y + 1);
    line_nb_pixels = 0;
    line_pixels = NULL;
    pixel_line(line4, &line_pixels, &line_nb_pixels);
    for (int i = 0; i < line_nb_pixels; i++) {
        (*pixel_tab)[(*nb_pixels)++] = line_pixels[i];
    }
    free(line4);
}

void pixel_rectangle(Shape *rectangle, Pixel ***pixel_tab, int *nb_pixels) {
    Rectangle *r = (Rectangle *) rectangle->ptrShape;
    int x = r->p->pos_x;
    int y = r->p->pos_y;
    int height = r->height;
    int width = r->width;

    *pixel_tab = malloc(sizeof(Pixel *) * ((height + width) * 2));
    *nb_pixels = 0;

    Shape *line1 = create_line_shape(x, y, x + width - 1, y);
    int line_nb_pixels = 0;
    Pixel **line_pixels = NULL;
    pixel_line(line1, &line_pixels, &line_nb_pixels);
    for (int i = 0; i < line_nb_pixels; i++) {
        (*pixel_tab)[(*nb_pixels)++] = line_pixels[i];
    }
    free(line1);

    Shape *line2 = create_line_shape(x + width, y, x + width, y + height - 1);
    line_nb_pixels = 0;
    line_pixels = NULL;
    pixel_line(line2, &line_pixels, &line_nb_pixels);
    for (int i = 0; i < line_nb_pixels; i++) {
        (*pixel_tab)[(*nb_pixels)++] = line_pixels[i];
    }
    free(line2);

    Shape *line3 = create_line_shape(x + width, y + height, x + 1, y + height);
    line_nb_pixels = 0;
    line_pixels = NULL;
    pixel_line(line3, &line_pixels, &line_nb_pixels);
    for (int i = 0; i < line_nb_pixels; i++) {
        (*pixel_tab)[(*nb_pixels)++] = line_pixels[i];
    }
    free(line3);

    Shape *line4 = create_line_shape(x, y + height, x, y + 1);
    line_nb_pixels = 0;
    line_pixels = NULL;
    pixel_line(line4, &line_pixels, &line_nb_pixels);
    for (int i = 0; i < line_nb_pixels; i++) {
        (*pixel_tab)[(*nb_pixels)++] = line_pixels[i];
    }
    free(line4);
}

int polygon_max_size(Polygon *polygon) {
    int max_size = 0;

    for (int j = 0; j < polygon->n; j++) {
        int x1 = polygon->points[j]->pos_x;
        int y1 = polygon->points[j]->pos_y;
        int x2 = polygon->points[(j + 1) % polygon->n]->pos_x;
        int y2 = polygon->points[(j + 1) % polygon->n]->pos_y;
        int dx = abs(x2 - x1);
        int dy = abs(y2 - y1);
        int size = dx > dy ? dx : dy; // Sélectionne la plus grande différence (x ou y) comme taille

        max_size += size + 1; // Ajoute la taille de l'arête (incluant les points extrémités)
    }

    return max_size;
}

void pixel_polygon(Shape *polygon, Pixel ***pixel_tab, int *nb_pixels) {
    Polygon *p = (Polygon *) polygon->ptrShape;
    int max_size = polygon_max_size(p);
    *pixel_tab = malloc(sizeof(Pixel *) * max_size);
    *nb_pixels = 0;
    // itere sur les points du polygone
    for (int j = 0; j < p->n; j++) {
        Shape * line_shape = create_line_shape(p->points[j]->pos_x, p->points[j]->pos_y,p->points[(j + 1) % p->n]->pos_x, p->points[(j + 1) % p->n]->pos_y);
        Pixel **line_pixels = NULL;
        int line_nb_pixels = 0;
        pixel_line(line_shape, &line_pixels, &line_nb_pixels);
        // copie les pixels de la ligne dans le tableau de pixels du polygone
        for (int i = 0; i < line_nb_pixels; i++) {
            (*pixel_tab)[(*nb_pixels)++] = line_pixels[i];
        }

        free(line_pixels);
    }
}


Pixel **create_shape_to_pixel(Shape *shape, int *nb_pixels) {
    // Utilisation de switch case pour appeler la bonne fonction selon le type de shape
    Pixel **pixel_tab = NULL;
    switch (shape->shape_type) {
        case POINT:
            pixel_point(shape, &pixel_tab, nb_pixels);
            break;
        case LINE:
            pixel_line(shape, &pixel_tab, nb_pixels);
            break;
        case CIRCLE:
            pixel_circle(shape, &pixel_tab, nb_pixels);
            break;
        case SQUARE:
            pixel_square(shape, &pixel_tab, nb_pixels);
            break;
        case RECTANGLE:
            pixel_rectangle(shape, &pixel_tab, nb_pixels);
            break;
        case POLYGON:
            pixel_polygon(shape, &pixel_tab, nb_pixels);
            break;
        default:
            printf("Erreur : type de shape inconnu\n");
            break;
    }
    return pixel_tab;
}

void delete_pixel_shape(Pixel ***pixel, int nb_pixels) {
    for (int i = 0; i < nb_pixels; i++) {
        delete_pixel((*pixel)[i]);
    }
    free(*pixel);
    *pixel = NULL;
}

// DOCUMENTATION

/**
 * @struct Pixel
 * @brief Structure représentant un pixel
 * @var Pixel::px
 * La coordonnée x du pixel
 * @var Pixel::py
 * La coordonnée y du pixel
 */

/**
 * @typedef Pixel
 * @brief Alias pour le type `struct Pixel`
 */

/**
 * @fn Pixel *create_pixel(int px, int py)
 * @brief Crée un nouveau pixel.
 * @param px La coordonnée x du pixel
 * @param py La coordonnée y du pixel
 * @return Un pointeur vers le pixel créé
 */

/**
 * @fn void delete_pixel(Pixel *pixel)
 * @brief Supprime un pixel.
 * @param pixel Le pixel à supprimer
 */

/**
 * @struct Shape
 * @brief Structure représentant une forme géométrique
 * @var Shape::shape_type
 * Le type de forme géométrique
 * @var Shape::ptrShape
 * Un pointeur vers la forme spécifique
 */

/**
 * @typedef Shape
 * @brief Alias pour le type `struct Shape`
 */

/**
 * @fn void pixel_point(Shape *shape, Pixel ***pixel_tab, int *nb_pixels)
 * @brief Convertit une forme point en pixels.
 * @param shape La forme point à convertir
 * @param pixel_tab Un pointeur vers un tableau de pixels
 * @param nb_pixels Un pointeur vers le nombre de pixels
 */

/**
 * @fn void pixel_line(Shape *line, Pixel ***pixel_tab, int *nb_pixels)
 * @brief Convertit une forme ligne en pixels.
 * @param line La forme ligne à convertir
 * @param pixel_tab Un pointeur vers un tableau de pixels
 * @param nb_pixels Un pointeur vers le nombre de pixels
 */

/**
 * @fn void pixel_circle(Shape *shape, Pixel ***pixel_tab, int *nb_pixels)
 * @brief Convertit une forme cercle en pixels.
 * @param shape La forme cercle à convertir
 * @param pixel_tab Un pointeur vers un tableau de pixels
 * @param nb_pixels Un pointeur vers le nombre de pixels
 */

/**
 * @fn void pixel_square(Shape *square, Pixel ***pixel_tab, int *nb_pixels)
 * @brief Convertit une forme carré en pixels.
 * @param square La forme carré à convertir
 * @param pixel_tab Un pointeur vers un tableau de pixels
 * @param nb_pixels Un pointeur vers le nombre de pixels
 */

/**
 * @fn void pixel_rectangle(Shape *rectangle, Pixel ***pixel_tab, int *nb_pixels)
 * @brief Convertit une forme rectangle en pixels.
 * @param rectangle La forme rectangle à convertir
 * @param pixel_tab Un pointeur vers un tableau de pixels
 * @param nb_pixels Un pointeur vers le nombre de pixels
 */

/**
 * @fn int polygon_max_size(Polygon *polygon)
 * @brief Calcule la taille maximale d'un polygone en termes de pixels.
 * @param polygon Le polygone dont on veut calculer la taille maximale
 * @return La taille maximale du polygone en termes de pixels
 */

/**
 * @fn void pixel_polygon(Shape *polygon, Pixel ***pixel_tab, int *nb_pixels)
 * @brief Convertit une forme polygonale en pixels.
 * @param polygon La forme polygonale à convertir
 * @param pixel_tab Un pointeur vers un tableau de pixels
 * @param nb_pixels Un pointeur vers le nombre de pixels
 */

/**
* @fn Pixel **create_shape_to_pixel(Shape *shape, int *nb_pixels)
 * @brief Convertit une forme en pixels.
 * @param shape La forme à convertir
 * @param nb_pixels Un pointeur vers le nombre de pixels
 * @return Un pointeur vers un tableau de pixels
 */

/**
* @fn void delete_pixel_shape(Pixel ***pixel, int nb_pixels)
 * @brief Supprime un tableau de pixels.
 * @param pixel Le tableau de pixels à supprimer
 * @param nb_pixels Le nombre de pixels
*/