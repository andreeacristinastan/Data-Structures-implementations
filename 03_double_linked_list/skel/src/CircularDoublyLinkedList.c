#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CircularDoublyLinkedList.h"
#include "utils.h"

/*
 * Functie care trebuie apelata pentru alocarea si initializarea unei liste.
 * (Setare valori initiale pentru campurile specifice structurii LinkedList).
 */
doubly_linked_list_t*
dll_create(unsigned int data_size)
{
    doubly_linked_list_t* list;

    list = malloc(sizeof(doubly_linked_list_t));
    DIE(list == NULL, "malloc failed");

    list->head = NULL;
    list->data_size = data_size;
    list->size = 0;

    return list;
}

/*
 * Functia intoarce un pointer la nodul de pe pozitia n din lista.
 * Pozitiile din lista sunt indexate incepand cu 0 (i.e. primul nod din lista se
 * afla pe pozitia n=0). Daca n >= nr_noduri, atunci se intoarce nodul de pe
 * pozitia rezultata daca am "cicla" (posibil de mai multe ori) pe lista si am
 * trece de la ultimul nod, inapoi la primul si am continua de acolo. Cum putem
 * afla pozitia dorita fara sa simulam intreaga parcurgere? Daca n < 0, eroare.
 */
dll_node_t*
dll_get_nth_node(doubly_linked_list_t* list, unsigned int n)
{
    dll_node_t *current;
    unsigned int i = 0;

    current = list->head;


    if(list == NULL) {
        return NULL;
    }

    if(n >= list->size) {
        n = n % list->size;
    }

    if(n < list->size) 
        while(i < n) {
            current = current->next;
            ++i;
        }

    return current;
}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e
 * adaugat pe pozitia n a listei reprezentata de pointerul list. Pozitiile din
 * lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla pe
 * pozitia n=0). Cand indexam pozitiile nu "ciclam" pe lista circulara ca la
 * get, ci consideram nodurile in ordinea de la head la ultimul (adica acel nod
 * care pointeaza la head ca nod urmator in lista). Daca n >= nr_noduri, atunci
 * adaugam nodul nou la finalul listei. Daca n < 0, eroare.
 */
void
dll_add_nth_node(doubly_linked_list_t* list, unsigned int n, const void* new_data)
{
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
        new_node->prev = list->head->prev;
        list->head->prev->next = new_node;
        list->head->prev = new_node;
        
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
        current->next->prev = new_node;
        current->next = new_node;
        list->size++;
    } else {
        list->head = new_node;
        new_node->next = new_node;
        new_node->prev = new_node;
        list->size++;
    }

}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca
 * parametru. Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din
 * lista se afla pe pozitia n=0). Functia intoarce un pointer spre acest nod
 * proaspat eliminat din lista. Daca n >= nr_noduri - 1, se elimina nodul de la
 * finalul listei. Daca n < 0, eroare. Este responsabilitatea apelantului sa
 * elibereze memoria acestui nod.
 */
dll_node_t*
dll_remove_nth_node(doubly_linked_list_t* list, unsigned int n)
{
    dll_node_t* removed_node,* last,* prev1;

    if(list == NULL || list->head == NULL)
        return NULL;
    
    if(list->head->next == NULL) {
        list->head = NULL;
        last = list->head;
    }

    if(n == 0 && list->size != 0) {
        removed_node = list->head;
        list->head = list->head->next;
        list->head->prev = removed_node->prev;
        removed_node->prev->next = list->head;

        last = removed_node;
    } else if(n >= list->size - 1) {
        last = list->head->next;
        prev1 = list->head;
        while(last->next != list->head) {
            prev1 = last;
            last = last->next;
        }
        prev1->next = list->head;
        list->head->prev = prev1;
    } else {
        unsigned int cnt = 0;
        last = list->head->next;
        prev1 = list->head;
        while(cnt < n-1) {
            prev1 = last;
            last = last->next;
            cnt ++;
        }
        prev1->next = last->next;
        last->next->prev = prev1;
    }
    
    list->size--;
    return last;
}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca
 * parametru.
 */
unsigned int
dll_get_size(doubly_linked_list_t* list)
{
     if(list == NULL)
        return -1;

    return list->size;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la
 * sfarsit, elibereaza memoria folosita de structura lista.
 */
void
dll_free(doubly_linked_list_t** pp_list)
{
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

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza toate valorile int stocate in nodurile
 * din lista separate printr-un spatiu, incepand de la primul nod din lista.
 */
void
dll_print_int_list(doubly_linked_list_t* list)
{
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
        while (current->next != list->head);

        printf("%d ", *((int *)current->data));
    }

    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza string-uri. Functia afiseaza toate string-urile stocate in
 * nodurile din lista separate printr-un spatiu, incepand de la primul nod din
 * lista.
 */
void
dll_print_string_list(doubly_linked_list_t* list)
{
      dll_node_t* current = list->head;

    if(list == NULL)
        return;
    if(list->size == 1) {
        printf("%s ", (char *)current->data);
    } else {
        do {
            printf("%s ", (char *)current->data);
            current = current->next;
        }
        while (current->next != list->head);

        printf("%s ", (char *)current->data);
    }

    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza o singura data toate valorile int
 * stocate in nodurile din lista, separate printr-un spatiu, incepand de la
 * nodul dat ca parametru si continuand la stanga in lista dublu inlantuita
 * circulara, pana cand sunt afisate valorile tuturor nodurilor.
 */
void
dll_print_ints_left_circular(dll_node_t* start)
{
    doubly_linked_list_t* list = NULL;
    dll_node_t* current = start;

    if(list == NULL)
        return;

    if(list->size == 1) {
        printf("%d ", *((int *)current->data));
    } else {
        do {
            printf("%d ", *((int *)current->data));
            current = current->prev;
        }
        while (current != start);

        printf("%d ", *((int *)current->data));
    }

    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza o singura data toate valorile int
 * stocate in nodurile din lista, separate printr-un spatiu, incepand de la
 * nodul dat ca parametru si continuand la dreapta in lista dublu inlantuita
 * circulara, pana cand sunt afisate valorile tuturor nodurilor.
 */
void
dll_print_ints_right_circular(dll_node_t* start)
{
    doubly_linked_list_t* list = NULL;
    dll_node_t* current = start;

    if(list == NULL)
        return;

    if(list->size == 1) {
        printf("%d ", *((int *)current->data));
    } else {
        do {
            printf("%d ", *((int *)current->data));
            current = current->next;
        }
        while (current != start);

        printf("%d ", *((int *)current->data));
    }
    
    printf("\n");
}
