#ifndef _LLIST_H
#define _LLIST_H

#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next;
    struct node *prev;
} node;

node *node_make(int value);
node *list_insert(node *prev_node, int value);
void list_print(const node *head);
node *list_find(node *head, int value);
void list_remove(node *n);
void list_free(node *head);

#endif
