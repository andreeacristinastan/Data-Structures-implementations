#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "utils.h"


void merge(linked_list_t* list1, linked_list_t* list2) {
   ll_node_t* current1 = list1->head,* current2 = list2->head;
   ll_node_t *next1, *next2;

   while(current1 != NULL && current2 != NULL) {
       next1 = current1->next;
       next2 = current2->next;

       current2->next = next1;
       current1->next = current2;

       current1 = next1;
       current2 = next2;
   }
   
}
