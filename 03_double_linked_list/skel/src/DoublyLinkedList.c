#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DoublyLinkedList.h"
#include "utils.h"

doubly_linked_list_t*
dll_create(unsigned int data_size) {
     doubly_linked_list_t* list;

    list = malloc(sizeof(doubly_linked_list_t));
    DIE(list == NULL, "malloc failed");

    list->head = NULL;
    list->data_size = data_size;
    list->size = 0;

    return list;
}

void
dll_add_nth_node(doubly_linked_list_t* list, unsigned int n, const void* new_data) {
    unsigned int i = 0;
    dll_node_t* new_node;
    dll_node_t* current;

    if(list == NULL) {
        return;
    }

    new_node = malloc(sizeof(dll_node_t));
    DIE(new_node == NULL, "malloc failed");
    new_node->data = malloc(list->data_size);
    DIE(new_data == NULL, "malloc failed");

    memcpy(new_node->data, new_data, list->data_size);

    if(n == 0 && list->size != 0) {
        new_node->next = list->head;
        list->head->prev = new_node;
        new_node->prev = NULL;

        
        list->head = new_node;
        list->size++;
        return;
    }
    
    if(n >= list->size) {
        n = list->size;
    }

    current = list->head;

    if(list->size != 0) {
        while(i < n-1) {
            current = current->next;
            i++;
        }
        new_node->next = current->next;
        new_node->prev = current;
        current->next = new_node;
        list->size++;
    } else {
        list->head = new_node;
        list->head->next = NULL;
        list->head->prev = NULL;
        list->size++;
    }
}

void
dll_free(doubly_linked_list_t** pp_list) {
    dll_node_t *current = (*pp_list)->head;

    if(* pp_list == NULL || pp_list == NULL)
        return;

    while((*pp_list)->size != 0) {
        (*pp_list)->head = (*pp_list)->head->next;
        free(current->data);
        free(current);
        current = (*pp_list)->head;
        (*pp_list)->size--;
    }
    free(* pp_list);
    *pp_list = NULL;
}

void
dll_print_int_list(doubly_linked_list_t* list) {
    dll_node_t* current = list->head;

    if(list == NULL)
        return;

    if(list->size == 1) {
        printf("%d ", *((int *)current->data));
    } else {
        do {
            printf("%d ", *((int *)current->data));
            current = current->next;
        }
        while (current->next != NULL);

        printf("%d ", *((int *)current->data));
    }

    printf("\n");
}

dll_node_t*
dll_remove_nth_node(doubly_linked_list_t* list, int cnt) {
    dll_node_t* removed_node,* last,* prev1;

    if(list == NULL || list->head == NULL)
        return NULL;
    
    if(list->head->next == NULL) {
        list->head = NULL;
        last = list->head;
    }

    if(cnt == 0 && list->size != 0) {
        removed_node = list->head;
        list->head = list->head->next;
        list->head->prev = NULL;

        last = removed_node;
    } else if(cnt >= list->size - 1) {
        last = list->head->next;
        prev1 = list->head;
        while(last->next != NULL) {
            prev1 = last;
            last = last->next;
        }
        prev1->next = NULL;
        list->head->prev = NULL;
    } else {
        unsigned int count = 0;
        last = list->head->next;
        prev1 = list->head;
        while(count < cnt-1) {
            prev1 = last;
            last = last->next;
            count ++;
        }
        prev1->next = last->next;
        last->next->prev = prev1;
    }
    
    list->size--;
    return last;
}

void reorder(doubly_linked_list_t* list, int integer) {
    dll_node_t* current = list->head,* last;
    int cnt = 0;

    if(list == NULL) {
        return;
    }
    
    while(current != NULL) {
        dll_node_t* next_current = current->next;

        if(*((int *)current->data) <= integer) {
            dll_node_t* removed_node = dll_remove_nth_node(list, cnt);

            removed_node->next = list->head;
            list->head->prev = removed_node;
            removed_node->prev = NULL;

            list->head = removed_node;
            list->size++;
        }
        current = next_current;
        cnt ++;
    }

}
