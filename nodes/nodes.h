#ifndef PROJET_NODES_H
#define PROJET_NODES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Liste chainées

struct lnode_ {
    void * data;
    struct lnode_ * prev;
    struct lnode_ * next;
};

typedef struct lnode_ lnode;

struct list_ {
    lnode * head;
    lnode * tail;
};

typedef struct list_ LIST;

lnode * lst_create_node(void * data);

LIST * lst_create_list();

void lst_delete_list(LIST * list);

void lst_insert_head(LIST * list, lnode * pnew);

void lst_insert_tail(LIST * list, lnode * pnew);

void lst_insert_after(LIST * list, lnode * pnew, lnode * ptr);

void lst_delete_head(LIST * list);

void lst_delete_tail(LIST * list);

void lst_delete_lnode(LIST * list, lnode * ptr);

void lst_erase(LIST * list);

lnode * get_first_node(LIST * list);

lnode * get_last_node(LIST * list);

lnode * get_next_node(LIST * list, lnode * lnode);

void * get_previous_elem(LIST * list, lnode * lnode);


#endif //PROJET_NODES_H
