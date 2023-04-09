#include <stdlib.h>

#include "Stack.h"
#include "utils.h"


stack_t *
st_create(unsigned int data_size)
{
	stack_t* stack;
	
	stack = malloc(sizeof(stack_t));
	DIE(!stack, "malloc failed");

	stack->list = ll_create(sizeof(data_size));
	stack->list->head = NULL;
	stack->list->size = 0;
	return stack;
}

unsigned int
st_get_size(stack_t *st)
{
	return st->list->size;
}

/*
 * Intoarce 1 daca stiva este goala si 0 in caz contrar.
 */
unsigned int
st_is_empty(stack_t *st)
{
	return st->list->size == 0;
}

void *
st_peek(stack_t *st)
{
	if(st_is_empty(st) == 0) {
		return st->list->head->data;
	} else	
		return NULL;
}

void
st_pop(stack_t *st)
{
	ll_node_t* removed = ll_remove_nth_node(st->list, 0);
	free(removed->data);
	free(removed);
}

void
st_push(stack_t *st, void *new_data)
{
	ll_add_nth_node(st->list, 0, new_data);
}

void
st_clear(stack_t *st)
{
	while(st->list->size != 0) {
		ll_node_t* removed = ll_remove_nth_node(st->list, 0);
		free(removed->data);
		free(removed);
	}
}

void
st_free(stack_t *st)
{
	st_clear(st);
	free(st->list);
	free(st);
}
