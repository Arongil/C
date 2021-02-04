#include <stdio.h>
#include <stdlib.h>
#include "llist.h"

node *node_make(int value) {
    node *n = malloc(sizeof(node));

    n->prev = NULL;
    n->next = NULL;
    n->value = value;

    return n;
}

node *list_insert(node *prev_node, int value) {
    node *n = node_make(value);

    n->prev = prev_node;
    n->next = prev_node->next;
    if (prev_node->next != NULL) {
        prev_node->next->prev = n;
    }
    prev_node->next = n;

    return n;
}

void list_print(const node *head) {
    printf("Head: %i\n", head->value);
    node *n = head->next;
    while (n != NULL) {
        printf("Next: %i\n", n->value);
        n = n->next;
    }
}

node *list_find(node *head, int value) {
    node *n = head;
    while (n != NULL) {
        if (n->value == value) {
            return n;
        }
        n = n->next;
    }
    return NULL;
}

void list_remove(node *n) {
    if (n->prev != NULL) {
        n->prev->next = n->next;
    }
    if (n->next != NULL) {
        n->next->prev = n->prev;
    }
    free(n);
}

void list_free(node *head) {
    if (head->next == NULL) {
        free(head);
        return;
    }
    list_free(head->next);
    free(head);
}
