#include <stdio.h>
#include <stdlib.h>
#include "llist.h"

int main(int argc, char *argv[]) {
    // Try out your code as you're building it here.
    // If you just run "make" in this directory, it
    // will compile this file and make an executable
    // called "main".
    
    // When you've got most of the functions in place,
    // try compiling the tests with "make test" and
    // running them via the executable called "test".

    node *head = node_make(1);
    printf("I made a node @ %p, with value %d!\n", head, head->value);

    list_insert(head, 5);
    list_insert(head, 3);

    printf("Head: %i \nnext: %i \nnext: %i", head->value, head->next->value, head->next->next->value);

    printf("\n\nUsing list_print...\n");
    
    list_print(head);

    printf("\nFind the first node with value 3...");

    node *three_node = list_find(head, 3);
    printf("\nNode found at %p with value %i", three_node, three_node->value);

    printf("\n\nAdding some more values, then testing removing one...\n");

    list_insert(head, 6);
    list_insert(head->next->next, 2);

    list_print(head);
    
    printf("\nRemoving a node...\n");
    list_remove(head->next->next);
    list_print(head);

    printf("\nRemoving last node...\n");
    list_remove(head->next->next->next);
    list_print(head);

    printf("\nFree the list.\n");
    list_free(head);

    return 0;
}
