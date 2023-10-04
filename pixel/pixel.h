#ifndef PROJET_PIXEL_H
#define PROJET_PIXEL_H

#include <stdio.h>
#include <stdlib.h>
#include "../shapes/shapes.h"

struct pixel {
    int px;
    int py;
};
typedef struct pixel Pixel;

Pixel *create_pixel(int px, int py);
void delete_pixel(Pixel *pixel);
void pixel_point(Shape * shape, Pixel *** pixel_tab, int * nb_pixels);
void pixel_line(Shape * line, Pixel *** pixel_tab, int * nb_pixels);
void pixel_circle(Shape * shape, Pixel *** pixel_tab, int * nb_pixels);
void pixel_square(Shape * square, Pixel *** pixel_tab, int * nb_pixels);
void pixel_rectangle(Shape * rectangle, Pixel *** pixel_tab, int * nb_pixels);
void pixel_polygon(Shape * polygon, Pixel *** pixel_tab, int * nb_pixels);
Pixel ** create_shape_to_pixel(Shape * shape, int * nb_pixels);
int polygon_max_size(Polygon * polygon);
#endif //PROJET_PIXEL_H
