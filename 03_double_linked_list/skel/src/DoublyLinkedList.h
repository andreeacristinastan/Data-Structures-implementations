#ifndef __DOUBLY_LINKED_LIST_H_
#define __DOUBLY_LINKED_LIST_H_
typedef struct dll_node_t dll_node_t;
struct dll_node_t
{
    void* data; /* Pentru ca datele stocate sa poata avea orice tip, folosim un
                   pointer la void. */
    dll_node_t *prev, *next;
};

typedef struct doubly_linked_list_t doubly_linked_list_t;
struct doubly_linked_list_t
{
    dll_node_t* head;
    unsigned int data_size;
    unsigned int size;
};

doubly_linked_list_t*
dll_create(unsigned int data_size);

void
dll_add_nth_node(doubly_linked_list_t* list, unsigned int n, const void* new_data);

void
dll_free(doubly_linked_list_t** pp_list);

void
dll_print_int_list(doubly_linked_list_t* list);

void
reorder(doubly_linked_list_t* list, int integer);

dll_node_t*
dll_remove_nth_node(doubly_linked_list_t* list, int cnt);

#endif /* __DOUBLY_LINKED_LIST_ */