#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "utils.h"

linked_list_t*
ll_create(unsigned int data_size)
{
    linked_list_t* list;
    
    list = malloc(sizeof(linked_list_t));
    DIE(list == NULL, "malloc failed");

    list->head = NULL;
    list->data_size = data_size;
    list->size = 0;

    return list;
}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e
 * adaugat pe pozitia n a listei reprezentata de pointerul list. Pozitiile din
 * lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla pe
 * pozitia n=0). Daca n >= nr_noduri, noul nod se adauga la finalul listei. Daca
 * n < 0, eroare.
 */
void
ll_add_nth_node(linked_list_t* list, unsigned int n, const void* new_data)
{
   unsigned int i;
    ll_node_t* new_node;
    ll_node_t* current;

    if(list == NULL) {
        return;
    }

    new_node = malloc(sizeof(ll_node_t));
    DIE(new_node == NULL, "malloc failed");
    new_node->data = malloc(list->data_size);
    DIE(new_data == NULL, "malloc failed");

    memcpy(new_node->data, new_data, list->data_size);
    
    if(n == 0) {
        new_node->next = list->head;
        list->head = new_node;
        list->size++;
        return;
    }

    if(n >= list->size) {
        n = list->size;
    }

    current = list->head;
    if(list->size != 0) {
        for( i = 0; i < n-1; i++) {
            current = current->next;
        }
    
    new_node->next = current->next;
    current->next = new_node;
    list->size++;
    } else {
        list->head = new_node;
        list->head->next = NULL;
        list->size++;
    }
}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca
 * parametru. Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din
 * lista se afla pe pozitia n=0). Daca n >= nr_noduri - 1, se elimina nodul de
 * la finalul listei. Daca n < 0, eroare. Functia intoarce un pointer spre acest
 * nod proaspat eliminat din lista. Este responsabilitatea apelantului sa
 * elibereze memoria acestui nod.
 */
ll_node_t*
ll_remove_nth_node(linked_list_t* list, unsigned int n)
{
    ll_node_t* removed_node,* last, * prev;

    if(list == NULL || list->head == NULL)
        return NULL;
    
    if(list->head->next == NULL) {
        list->head = NULL;
        last = list->head;
    }

    if(n == 0) {
        removed_node = list->head;   
        list->head = removed_node->next;
        last = removed_node;
    } else if(n >= list->size - 1) {
        last = list->head->next;
        prev = list->head;
        while(last->next != NULL) {
            prev = last;
            last = last->next;
        }
        prev->next = NULL;
    } else {
        unsigned int cnt = 0;
        last = list->head->next;
        prev = list->head;
        while(cnt <= n-1) {
            prev = last;
            last = last->next;
            cnt ++;
        }
        prev->next = NULL;
    }
    
    list->size--;
    return last;
}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca
 * parametru.
 */
unsigned int
ll_get_size(linked_list_t* list)
{
   if(list == NULL)
        return -1;

    return list->size;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la
 * sfarsit, elibereaza memoria folosita de structura lista si actualizeaza la
 * NULL valoarea pointerului la care pointeaza argumentul (argumentul este un
 * pointer la un pointer).
 */
void
ll_free(linked_list_t** pp_list)
{
    ll_node_t *current = (*pp_list)->head;

    if(* pp_list == NULL || pp_list == NULL)
        return;

    while((*pp_list)->head != NULL) {
        (*pp_list)->head = (*pp_list)->head->next;
        free(current->data);
        free(current);
        current = (*pp_list)->head;
    }
    free(* pp_list);
    *pp_list = NULL;
  
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza toate valorile int stocate in nodurile
 * din lista inlantuita separate printr-un spatiu.
 */
void
ll_print_int(linked_list_t* list)
{
    ll_node_t* current = list->head;

    if(list == NULL)
        return;
    
    while (current != NULL) {
        printf("%d ", *((int *)current->data));
        current = current->next;
    }

    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza string-uri. Functia afiseaza toate string-urile stocate in
 * nodurile din lista inlantuita, separate printr-un spatiu.
 */
void
ll_print_string(linked_list_t* list)
{
    ll_node_t* current = list->head;

    if(list == NULL)
        return;
    
    while (current != NULL) {
        printf("%s ", (char *)current->data);
        current = current->next;
    }

    printf("\n");

}
