#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "ListGraph.h"

list_graph_t*
lg_create(int nodes)
{
	list_graph_t* graph = malloc(sizeof(list_graph_t));
	DIE(graph == NULL, "malloc failed");

	graph->nodes = nodes;
	
	graph->neighbors = malloc(nodes * sizeof(linked_list_t*));
	DIE(graph->neighbors == NULL, "malloc failed");

	for(int i = 0; i < nodes; i++) {
		graph->neighbors[i] = ll_create(sizeof(int));
	}

	return graph;

}

void
lg_add_edge(list_graph_t* graph, int src, int dest)
{
	DIE(graph == NULL, "malloc failed");
	DIE(graph->neighbors == NULL, "malloc failed");

	int exist = 0;
	ll_node_t* current = graph->neighbors[src]->head;

	while(current != NULL) {
		if(*(int *)current->data == dest) {
			exist++;
			return;
		}
		current = current->next;
	}

	if(exist == 0)
		ll_add_nth_node(graph->neighbors[src], ll_get_size(graph->neighbors[src]), &dest);

}

int
lg_has_edge(list_graph_t* graph, int src, int dest)
{
	DIE(graph == NULL, "malloc failed");

	ll_node_t *current = graph->neighbors[src]->head;

	while(current != NULL) {
		if(*(int *)current->data == dest)
			return 1;
		current = current->next;
	}
	return 0;
}

linked_list_t*
lg_get_neighbours(list_graph_t* graph, int node)
{
	return graph->neighbors[node];
}

void
lg_remove_edge(list_graph_t* graph, int src, int dest)
{
	DIE(graph == NULL, "malloc failed");

	ll_node_t *current = graph->neighbors[src]->head;
	ll_node_t *removed;

	for(int i = 0; i < ll_get_size(graph->neighbors[src]); i++) {
		if(*(int *)current->data == dest) {
			removed = ll_remove_nth_node(graph->neighbors[src], i);
			free(removed->data);
			free(removed);
			return;
		}
		current = current->next;
	}
}

void
lg_free(list_graph_t* graph)
{
	DIE(graph == NULL, "malloc failed");
	
	for(int i = 0; i < graph->nodes; i++) {
		ll_free(&graph->neighbors[i]);
	}
	free(graph->neighbors);
	free(graph);
}