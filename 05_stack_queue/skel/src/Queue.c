#include <stdlib.h>
#include <string.h>

#include "Queue.h"
#include "utils.h"

queue_t *
q_create(unsigned int data_size, unsigned int max_size)
{
	queue_t* q;
	q = malloc(sizeof(queue_t));
	DIE(!q, "malloc failed");
	q->buff = malloc(max_size * sizeof(void *));
	DIE(!q->buff, "malloc failed");

	q->max_size = max_size;
	q->size = 0;
	q->write_idx = 0;
	q->read_idx = 0;
	q->data_size = data_size;
	return q;
}

unsigned int
q_get_size(queue_t *q)
{
	return q->size;
}

/*
 * Intoarce 1 daca stiva este goala si 0 in caz contrar.
 */
unsigned int
q_is_empty(queue_t *q)
{
	return q->size == 0;
}

void *
q_front(queue_t *q)
{
	if(q->size != 0)
		return q->buff[q->read_idx];
	else
		return NULL;
}

/* Functia intoarce true daca operatia s-a efectuat si false in caz contrar */
bool
q_dequeue(queue_t *q)
{
	if(q->size == 0)
		return false;
	else {
		free(q->buff[q->read_idx]);
		q->read_idx = (q->read_idx + 1) % q->max_size;
		q->size--;
		return true;
	}
}

/* Functia intoarce true daca operatia s-a efectuat si false in caz contrar */
bool
q_enqueue(queue_t *q, void *new_data)
{
	if(q->size == q->max_size)
		return false;
	else {
		q->buff[q->write_idx] = malloc(q->data_size);
		DIE(!q->buff[q->write_idx], "malloc failed");

		memcpy(q->buff[q->write_idx], new_data, q->data_size);
		q->write_idx = (q->write_idx + 1) % q->max_size;
		q->size++;
		return true;
	}
}

void
q_clear(queue_t *q)
{
	for(int i = 0; i < q->size; i++) {
		if(q->buff[i] != NULL)
			free(q->buff[i]);
	}
	q->write_idx = 0;
	q->read_idx = 0;
	q->size = 0;

}

void
q_free(queue_t *q)
{
	q_clear(q);
	free(q->buff);
	free(q);
}
