#ifndef PROJET_ARRAY_H
#define PROJET_ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../shapes/shapes.h"


#define MAX_SIZE 100

struct array {
    unsigned int max_size;
    unsigned int size;
    void *tab[MAX_SIZE];
};

typedef struct array Array;

Array *array_create();

void array_delete(Array *array);

unsigned int array_get_size_max(Array *array);

unsigned int array_get_size(Array *array);

void *array_get_element_at(Array *array, int pos);

int array_insert_element(Array *array, void *element);

// Layer part

#define VISIBLE 0
#define UNVISIBLE 1

struct layer {
    unsigned int id;
    char name[255];
    unsigned char visible;
    Array shapes;
};
typedef struct layer Layer;
typedef Array LayersList; // ici on va utiliser notre type Array

Layer *create_layer(int id, char *name);

void delete_layer(Layer *layer);

LayersList * create_layers_list();

void delete_layers_list(LayersList *layer_list);

void add_layer_to_list(LayersList *layer_list, Layer *layer);

void remove_layer_from_list(LayersList *layer_list, Layer *layer);

void set_layer_visible(Layer *layer);

void set_layer_unvisible(Layer *layer);

void add_shape_to_layer(Layer *layer, Shape *shape);

void remove_shape_to_from(Layer *layer, Shape *shape);

#endif //PROJET_ARRAY_H
