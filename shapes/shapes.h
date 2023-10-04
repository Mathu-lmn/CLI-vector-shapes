#ifndef PROJET_SHAPES_H
#define PROJET_SHAPES_H

#include <stdio.h>
#include <stdlib.h>
#include "../id/id.h"

// Point

typedef struct {
    int pos_x;
    int pos_y;
} Point;

Point * create_point(int px, int py);
void delete_point(Point * point);
void print_point(Point * p);

// Line

typedef struct {
    Point * p1;
    Point * p2;
} Line;

Line * create_line(Point * p1, Point * p2);
void delete_line(Line * line);
void print_line(Line * line);

// Square

typedef struct {
    Point * p;
    int length;
} Square;

Square * create_square(Point * p, int length);
void delete_square(Square * square);
void print_square(Square * square);

// Rectangle

typedef struct {
    Point * p;
    int width;
    int height;
} Rectangle;

Rectangle * create_rectangle(Point * p, int width, int height);
void delete_rectangle(Rectangle * rectangle);
void print_rectangle(Rectangle * rectangle);

// Circle

typedef struct {
    Point * center;
    int radius;
} Circle;

Circle * create_circle(Point * center, int radius);
void delete_circle(Circle * circle);
void print_circle(Circle * circle);

// Polygon

typedef struct {
    int n;
    Point ** points; // Tableau dynamique de points
} Polygon;

Polygon * create_polygon(int n, Point ** points);
void delete_polygon(Polygon * polygon);
void print_polygon(Polygon * polygon);

// Shape

typedef enum {
    POINT,
    LINE,
    SQUARE,
    RECTANGLE,
    CIRCLE,
    POLYGON
} SHAPE_TYPE;

typedef struct {
    int id;
    SHAPE_TYPE shape_type;
    void * ptrShape;
} Shape;

Shape * create_empty_shape(SHAPE_TYPE shape_type);
Shape * create_point_shape(int px, int py);
Shape * create_line_shape(int px1, int py1, int px2, int py2);
Shape * create_square_shape(int px, int py, int length);
Shape * create_rectangle_shape(int px, int py, int width, int height);
Shape * create_circle_shape(int px, int py, int radius);
Shape * create_polygon_shape(int lst[], int n);
void delete_shape(Shape * shape);
void print_shape(Shape * shape);

#endif //PROJET_SHAPES_H
