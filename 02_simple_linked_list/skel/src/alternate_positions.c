#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "alternate_positions.h"
#include "LinkedList.h"

int main() {
    int x;
    long nr, pos;
    char added_elem[64], *end_ptr;

    linked_list_t* list1,* list2;

    list1 = ll_create(sizeof(int));
    list2 = ll_create(sizeof(int));

    scanf("%d",&x);

    for(int i = 0; i < x; i++) {
        scanf("%ld", &pos);
        scanf("%s", added_elem);

        nr = strtol(added_elem, &end_ptr, 10);

        ll_add_nth_node(list1, pos, &nr);
    }

    for(int i = 0; i < x; i++) {
        scanf("%ld", &pos);
        scanf("%s", added_elem);

        nr = strtol(added_elem, &end_ptr, 10);

        ll_add_nth_node(list2, pos, &nr);
    }

    merge(list1, list2);
    ll_print_int(list1);

    list1->size *= 2;
    list2->size = 0;
    free(list2);
    ll_free(&list1);

    return 0;
}