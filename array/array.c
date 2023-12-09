/**
 * @file array.c
 * @author Mathurin Lemoine / Chengfeng Ding
 * @brief Fichier contenant les fonctions de gestion de listes
 * @version 1.0
 * @date 03/06/2023
 */

#include "array.h"

Array *array_create() {
    Array *array = (Array *) malloc(sizeof(Array));
    array->size = 0;
    array->max_size = MAX_SIZE;
    return array;
}

void array_delete(Array *array) {
    free(array);
}

unsigned int array_get_size_max(Array *array) {
    return array->max_size;
}

unsigned int array_get_size(Array *array) {
    return array->size;
}

void * array_get_element_at(Array *array, int pos) {
    if (pos < array_get_size(array))
        return array->tab[pos];
    return NULL;
}

int array_insert_element(Array *array, void *element) {
    if (array_get_size(array) >= array_get_size_max(array))
        return -1;
    array->tab[array_get_size(array)] = element;
    int temp = (int) array->size;
    array->size = array->size + 1;
    return temp;
}

// Layers

Layer * create_layer(int id, char *name) {
    Layer *layer = (Layer *) malloc(sizeof(Layer));
    layer->id = id;
    if (name != NULL)
        strcpy(layer->name, name);
    else
        sprintf(layer->name, "layer_%d", id);
    layer->visible = VISIBLE;
    layer->shapes = * array_create();
    return layer;
}

void delete_layer(Layer *layer) {
    array_delete(&layer->shapes);
    free(layer);
}

LayersList * create_layers_list() {
    LayersList *layers_list = (LayersList *) malloc(sizeof(LayersList));
    layers_list->size = 0;
    layers_list->max_size = MAX_SIZE;
    return layers_list;
}

void delete_layers_list(LayersList *layer_list) {
    for (int i = 0; i < layer_list->size; ++i) {
        delete_layer(layer_list->tab[i]);
        free(layer_list->tab[i]);
        layer_list->tab[i] = NULL;
    }
    free(layer_list);
    layer_list = NULL;
}

void add_layer_to_list(LayersList *layer_list, Layer *layer) {
    array_insert_element(layer_list, layer);
}

void remove_layer_from_list(LayersList *layer_list, Layer *layer) {
    for (int i = 0; i < layer_list->size; ++i) {
        if (layer_list->tab[i] == layer) {
            delete_layer(layer_list->tab[i]);
            free(layer_list->tab[i]);
            layer_list->tab[i] = NULL;
            // déplacer les éléments suivants d'une case vers la gauche et réduire la taille de 1
            for (int j = i; j < layer_list->size - 1; ++j) {
                layer_list->tab[j] = layer_list->tab[j + 1];
            }
            layer_list->size--;
            break;
        }
    }
}

void set_layer_visible(Layer *layer) {
    layer->visible = VISIBLE;
}

void set_layer_unvisible(Layer *layer) {
    layer->visible = UNVISIBLE;
}

void add_shape_to_layer(Layer *layer, Shape *shape) {
    array_insert_element(&layer->shapes, shape);
}

void remove_shape_to_from(Layer *layer, Shape *shape) {
    for (int i = 0; i < layer->shapes.size; ++i) {
        if (layer->shapes.tab[i] == shape) {
            delete_shape(layer->shapes.tab[i]);
            free(layer->shapes.tab[i]);
            layer->shapes.tab[i] = NULL;
            // déplacer les éléments suivants d'une case vers la gauche et réduire la taille de 1
            for (int j = i; j < layer->shapes.size - 1; ++j) {
                layer->shapes.tab[j] = layer->shapes.tab[j + 1];
            }
            layer->shapes.size--;
            break;
        }
    }
}

