#include <stdio.h>
#include <stdlib.h>
#include "DoublyLinkedList.h"
#include "utils.h"

int main() {
    int x, integer;
    long nr, pos;
    char added_elem[64], *end_ptr;

    doubly_linked_list_t* list;

    list = dll_create(sizeof(int));

    scanf("%d%d", &x, &integer);

    for(int i = 0; i < x; i++) {
        scanf("%ld", &pos);
        scanf("%s", added_elem);

        nr = strtol(added_elem, &end_ptr, 10);

        dll_add_nth_node(list, pos, &nr);
    }

   reorder(list, integer);

    dll_print_int_list(list);

    dll_free(&list);

    return 0;
}