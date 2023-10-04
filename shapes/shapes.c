/**
 * @file shapes.c
 * @author Mathurin Lemoine / Chengfeng Ding
 * @brief Fichier contenant les fonctions de gestion des formes
 * @version 1.0
 * @date 03/06/2023
 */

#include "shapes.h"

// Point

Point *create_point(int px, int py) {
    Point *p = malloc(sizeof(Point));
    p->pos_x = px;
    p->pos_y = py;
    return p;
}

void delete_point(Point *point) {
    free(point);
}

void print_point(Point *p) {
    printf("POINT [%d,%d]\n", p->pos_x, p->pos_y);
}

// Line

Line *create_line(Point *p1, Point *p2) {
    Line *l = malloc(sizeof(Line));
    l->p1 = p1;
    l->p2 = p2;
    return l;
}

void delete_line(Line *line) {
    free(line);
}

void print_line(Line *line) {
    printf("LINE [%d,%d] [%d,%d]\n", line->p1->pos_x, line->p1->pos_y, line->p2->pos_x, line->p2->pos_y);
}

// Square

Square *create_square(Point *p, int length) {
    Square *s = malloc(sizeof(Square));
    s->p = p;
    s->length = length;
    return s;
}

void delete_square(Square *square) {
    free(square);
}

void print_square(Square *square) {
    printf("SQUARE [%d,%d] %d\n", square->p->pos_x, square->p->pos_y, square->length);
}

// Rectangle

Rectangle *create_rectangle(Point *p, int width, int height) {
    Rectangle *r = malloc(sizeof(Rectangle));
    r->p = p;
    r->width = width;
    r->height = height;
    return r;
}

void delete_rectangle(Rectangle *rectangle) {
    free(rectangle);
}

void print_rectangle(Rectangle *rectangle) {
    printf("RECTANGLE [%d,%d] %d %d\n", rectangle->p->pos_x, rectangle->p->pos_y, rectangle->width, rectangle->height);
}

// Circle

Circle *create_circle(Point *center, int radius) {
    Circle *c = malloc(sizeof(Circle));
    c->center = center;
    c->radius = radius;
    return c;
}

void delete_circle(Circle *circle) {
    free(circle);
}

void print_circle(Circle *circle) {
    printf("CIRCLE [%d,%d] %d\n", circle->center->pos_x, circle->center->pos_y, circle->radius);
}

// Polygon

Polygon *create_polygon(int n, Point ** points) {
    Polygon *p = malloc(sizeof(Polygon));
    p->n = n;
    p->points = points;
    return p;
}

void delete_polygon(Polygon *polygon) {
    free(polygon);
}

void print_polygon(Polygon *polygon) {
    printf("POLYGON\n");
    for (int i = 0; i < polygon->n; i++) {
        printf("  [%d,%d]\n", polygon->points[i]->pos_x, polygon->points[i]->pos_y);
    }
}

// Shape

Shape * create_empty_shape(SHAPE_TYPE shape_type) {
    Shape *shp = (Shape *) malloc(sizeof(Shape));
    shp->ptrShape = NULL;
    shp->id = get_next_id();
    shp->shape_type = shape_type;
    return shp;
}

Shape * create_point_shape(int px, int py) {
    Shape *shp = create_empty_shape(POINT);
    Point *p = create_point(px, py);
    shp->ptrShape = p;
    return shp;
}

Shape * create_line_shape(int px1, int py1, int px2, int py2) {
    Shape *shp = create_empty_shape(LINE);
    Point *p1 = create_point(px1, py1);
    Point *p2 = create_point(px2, py2);
    Line *l = create_line(p1, p2);
    shp->ptrShape = l;
    return shp;
}

Shape * create_square_shape(int px, int py, int length) {
    Shape *shp = create_empty_shape(SQUARE);
    Point *p1 = create_point(px, py);
    Square *s = create_square(p1, length);
    shp->ptrShape = s;
    return shp;
}

Shape * create_rectangle_shape(int px, int py, int width, int height) {
    Shape *shp = create_empty_shape(RECTANGLE);
    Point *p1 = create_point(px, py);
    Rectangle *r = create_rectangle(p1, width, height);
    shp->ptrShape = r;
    return shp;
}

Shape * create_circle_shape(int px, int py, int radius) {
    Shape *shp = create_empty_shape(CIRCLE);
    Point *p1 = create_point(px, py);
    Circle *c = create_circle(p1, radius);
    shp->ptrShape = c;
    return shp;
}

Shape * create_polygon_shape(int lst[], int n) {
    if (n % 2 != 0) {
        printf("ERROR : Les polygones doivent avoir un nombre pair d'elements\n");
        return NULL;
    }
    Point ** tab = malloc(sizeof(Point *) * (n / 2));
    for (int i = 0; i < n; i+= 2) {
        tab[i / 2] = create_point(lst[i], lst[i + 1]);
    }
    Shape *shp = create_empty_shape(POLYGON);
    Polygon *p = create_polygon(n/2, tab);
    shp->ptrShape = p;
    return shp;
}

void delete_shape(Shape *shape) {
    free(shape->ptrShape);
    free(shape);
}

void print_shape(Shape *shape) {
    printf("SHAPE : ID = %d\n", shape->id);
    switch (shape->shape_type) {
        case POINT:
            print_point(shape->ptrShape);
            break;
        case LINE:
            print_line(shape->ptrShape);
            break;
        case SQUARE:
            print_square(shape->ptrShape);
            break;
        case RECTANGLE:
            print_rectangle(shape->ptrShape);
            break;
        case CIRCLE:
            print_circle(shape->ptrShape);
            break;
        case POLYGON:
            print_polygon(shape->ptrShape);
            break;
    }
}


// DOCUMENTATION

/**
 * @struct Point
 * @brief Structure représentant un point
 * @var Point::pos_x
 * La coordonnée X du point
 * @var Point::pos_y
 * La coordonnée Y du point
 */

/**
 * @struct Line
 * @brief Structure représentant une ligne
 * @var Line::p1
 * Le premier point de la ligne
 * @var Line::p2
 * Le deuxième point de la ligne
 */

/**
 * @struct Square
 * @brief Structure représentant un carré
 * @var Square::p
 * Le point en haut à gauche du carré
 * @var Square::length
 * La longueur du côté du carré
 */

/**
 * @struct Rectangle
 * @brief Structure représentant un rectangle
 * @var Rectangle::p
 * Le point en haut à gauche du rectangle
 * @var Rectangle::width
 * La largeur du rectangle
 * @var Rectangle::height
 * La hauteur du rectangle
 */

/**
 * @struct Circle
 * @brief Structure représentant un cercle
 * @var Circle::center
 * Le centre du cercle
 * @var Circle::radius
 * Le rayon du cercle
 */

/**
 * @struct Polygon
 * @brief Structure représentant un polygone
 * @var Polygon::n
 * Le nombre de points du polygone
 * @var Polygon::points
 * Tableau des points du polygone
 */

/**
 * @typedef Point
 * @brief Alias pour le type `struct Point`
 */

/**
 * @typedef Line
 * @brief Alias pour le type `struct Line`
 */

/**
 * @typedef Square
 * @brief Alias pour le type `struct Square`
 */

/**
 * @typedef Rectangle
 * @brief Alias pour le type `struct Rectangle`
 */

/**
 * @typedef Circle
 * @brief Alias pour le type `struct Circle`
 */

/**
 * @typedef Polygon
 * @brief Alias pour le type `struct Polygon`
 */

/**
 * @fn Point *create_point(int px, int py)
 * @brief Crée un nouveau point.
 * @param px La coordonnée X du point
 * @param py La coordonnée Y du point
 * @return Un pointeur vers le point créé
 */

/**
 * @fn void delete_point(Point *point)
 * @brief Supprime un point et libère la mémoire associée.
 * @param point Le point à supprimer
 */

/**
 * @fn void print_point(Point *p)
 * @brief Affiche les coordonnées d'un point.
 * @param p Le point à afficher
 */

/**
 * @fn Line *create_line(Point *p1, Point *p2)
 * @brief Crée une nouvelle ligne à partir de deux points.
 * @param p1 Le premier point de la ligne
 * @param p2 Le deuxième point de la ligne
 * @return Un pointeur vers la ligne créée
 */

/**
 * @fn void delete_line(Line *line)
 * @brief Supprime une ligne et libère la mémoire associée.
 * @param line La ligne à supprimer
 */

/**
 * @fn void print_line(Line *line)
 * @brief Affiche les coordonnées des deux points formant la ligne.
 * @param line La ligne à afficher
 */

/**
 * @fn Square *create_square(Point *p, int length)
 * @brief Crée un nouveau carré à partir d'un point et de la longueur d'un côté.
 * @param p Le point en haut à gauche du carré
 * @param length La longueur du côté du carré
 * @return Un pointeur vers le carré créé
 */

/**
 * @fn void delete_square(Square *square)
 * @brief Supprime un carré et libère la mémoire associée.
 * @param square Le carré à supprimer
 */

/**
 * @fn void print_square(Square *square)
 * @brief Affiche les coordonnées du point en haut à gauche du carré et la longueur du côté.
 * @param square Le carré à afficher
 */

/**
 * @fn Rectangle *create_rectangle(Point *p, int width, int height)
 * @brief Crée un nouveau rectangle à partir d'un point, d'une largeur et d'une hauteur.
 * @param p Le point en haut à gauche du rectangle
 * @param width La largeur du rectangle
 * @param height La hauteur du rectangle
 * @return Un pointeur vers le rectangle créé
 */

/**
 * @fn void delete_rectangle(Rectangle *rectangle)
 * @brief Supprime un rectangle et libère la mémoire associée.
 * @param rectangle Le rectangle à supprimer
 */

/**
 * @fn void print_rectangle(Rectangle *rectangle)
 * @brief Affiche les coordonnées du point en haut à gauche du rectangle, la largeur et la hauteur.
 * @param rectangle Le rectangle à afficher
 */

/**
 * @fn Circle *create_circle(Point *center, int radius)
 * @brief Crée un nouveau cercle à partir d'un centre et d'un rayon.
 * @param center Le centre du cercle
 * @param radius Le rayon du cercle
 * @return Un pointeur vers le cercle créé
 */

/**
 * @fn void delete_circle(Circle *circle)
 * @brief Supprime un cercle et libère la mémoire associée.
 * @param circle Le cercle à supprimer
 */

/**
 * @fn void print_circle(Circle *circle)
 * @brief Affiche les coordonnées du centre du cercle et le rayon.
 * @param circle Le cercle à afficher
 */

/**
 * @fn Polygon *create_polygon(int n, Point **points)
 * @brief Crée un nouveau polygone à partir d'un nombre de points et d'un tableau de points.
 * @param n Le nombre de points du polygone
 * @param points Le tableau des points du polygone
 * @return Un pointeur vers le polygone créé
 */

/**
 * @fn void delete_polygon(Polygon *polygon)
 * @brief Supprime un polygone et libère la mémoire associée.
 * @param polygon Le polygone à supprimer
 */

/**
 * @fn void print_polygon(Polygon *polygon)
 * @brief Affiche les coordonnées de tous les points du polygone.
 * @param polygon Le polygone à afficher
 */

/**
 * @fn Shape * create_empty_shape(SHAPE_TYPE shape_type)
 * @brief Crée une nouvelle forme vide.
 * @param shape_type Le type de la forme
 * @return Un pointeur vers la forme créée
 */

/**
 * @fn Shape * create_point_shape(int px, int py)
 * @brief Crée une nouvelle forme de point à partir des coordonnées X et Y.
 * @param px La coordonnée X du point
 * @param py La coordonnée Y du point
 * @return Un pointeur vers la forme de point créée
 */

/**
 * @fn Shape * create_line_shape(int px1, int py1, int px2, int py2)
 * @brief Crée une nouvelle forme de ligne à partir des coordonnées des deux points formant la ligne.
 * @param px1 La coordonnée X du premier point
 * @param py1 La coordonnée Y du premier point
 * @param px2 La coordonnée X du deuxième point
 * @param py2 La coordonnée Y du deuxième point
 * @return Un pointeur vers la forme de ligne créée
 */

/**
 * @fn Shape * create_square_shape(int px, int py, int length)
 * @brief Crée une nouvelle forme de carré à partir des coordonnées du point en haut à gauche et de la longueur du côté.
 * @param px La coordonnée X du point en haut à gauche du carré
 * @param py La coordonnée Y du point en haut à gauche du carré
 * @param length La longueur du côté du carré
 * @return Un pointeur vers la forme de carré créée
 */

/**
 * @fn Shape * create_rectangle_shape(int px, int py, int width, int height)
 * @brief Crée une nouvelle forme de rectangle à partir des coordonnées du point en haut à gauche, de la largeur et de la hauteur.
 * @param px La coordonnée X du point en haut à gauche du rectangle
 * @param py La coordonnée Y du point en haut à gauche du rectangle
 * @param width La largeur du rectangle
 * @param height La hauteur du rectangle
 * @return Un pointeur vers la forme de rectangle créée
 */

/**
 * @fn Shape * create_circle_shape(int px, int py, int radius)
 * @brief Crée une nouvelle forme de cercle à partir des coordonnées du centre et du rayon.
 * @param px La coordonnée X du centre du cercle
 * @param py La coordonnée Y du centre du cercle
 * @param radius Le rayon du cercle
 * @return Un pointeur vers la forme de cercle créée
 */

/**
 * @fn Shape * create_polygon_shape(int lst[], int n)
 * @brief Crée une nouvelle forme de polygone à partir d'une liste de coordonnées.
 * @param lst La liste des coordonnées des points du polygone, sous forme [x1, y1, x2, y2, ..., xn, yn]
 * @param n Le nombre de points du polygone
 * @return Un pointeur vers la forme de polygone créée, ou NULL en cas d'erreur
 */

/**
 * @fn void delete_shape(Shape *shape)
 * @brief Supprime une forme et libère la mémoire associée.
 * @param shape La forme à supprimer
 */

/**
 * @fn void print_shape(Shape *shape)
 * @brief Affiche les informations de la forme.
 * @param shape La forme à afficher
 */