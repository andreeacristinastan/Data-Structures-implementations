#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ListGraph.h"
#include "Queue.h"
#include "Stack.h"
#include "utils.h"


#define MAX_NODES	100
#define INF		0x3f3f3f3f

/**
 * Adaugati nodurile componentei conexe curente in lista component. 
 */
static void
dfs_connected_comps(
	list_graph_t *lg,
	int node,
	int *visited,
	linked_list_t *component
) {
	visited[node] = 1;
	ll_add_nth_node(component, component->size, &node);
	
	ll_node_t* current = lg->neighbors[node]->head;

	while(current) {
		int neighbor = *((int*)current->data);
		if(!visited[neighbor]) {
			dfs_connected_comps(lg, neighbor, visited, component);
		}
		current = current->next;
	}

}

static linked_list_t **
connected_components(list_graph_t *lg, int *visited, unsigned int *num_comp)
{
	linked_list_t **comps = malloc(lg->nodes * sizeof(*comps));
	DIE(!comps, "malloc comps failed");
	visited = (int *)calloc(MAX_NODES, sizeof(int));
	DIE(visited == NULL, "calloc failed");
	/* TODO: adaugati fiecare componenta conexa ca o noua lista in comps */
	
	for(int i = 0; i < lg->nodes; i++) {
		if(!visited[i]) {
			linked_list_t* component = ll_create(sizeof(int));
			dfs_connected_comps(lg, i, visited, component);
			comps[*num_comp] = component;
			*num_comp = *num_comp + 1;
		}
	}

	free(visited);
	return comps;
}

static void
dfs_topo_sort(list_graph_t *lg, int node, int *visited, linked_list_t *sorted)
{
	visited[node] = 1;
	ll_node_t* current = lg->neighbors[node]->head;

	while(current) {
		int neighbor = *((int*)current->data);
		if(!visited[neighbor]) {
			dfs_topo_sort(lg, neighbor, visited, sorted);
		}
		current = current->next;
	}

	ll_add_nth_node(sorted, 0, &node);
}

static linked_list_t *
topo_sort(list_graph_t *lg, int *visited)
{
	linked_list_t *sorted = ll_create(sizeof(int));
	visited = (int *)calloc(MAX_NODES, sizeof(int));
	DIE(visited == NULL, "calloc failed");
	
	/* TODO: adaugati nodurile in lista sorted, in ordinea corecta */
	for(int i = 0; i < lg->nodes; i++) {
		if(!visited[i]) {
			dfs_topo_sort(lg, i, visited, sorted);
		}
	}

	free(visited);
	return sorted;
}

void
bfs_initialization(int *visit, int *parent, int node) {
	for(int i = 0; i < node; i++) {
		visit[i] = 0;
		parent[i] = -1;
	}
}

static void
min_path(list_graph_t *lg, int start, int *dist)
{

	int visit[MAX_NODES], parent[MAX_NODES], path[MAX_NODES];
	int count = 0, dest;
	scanf("%d", &dest);

	bfs_initialization(visit, parent, MAX_NODES);
	queue_t *q = q_create(sizeof(int), MAX_NODES);
	visit[start] = 1;
	dist[start] = 0;
	q_enqueue(q, &start);

	while(!q_is_empty(q)) {
		int neighbor = *(int*)q_front(q);
		q_dequeue(q);
		ll_node_t* current = lg->neighbors[neighbor]->head;

		while(current) {
			if(visit[*(int*)(current->data)] == 0) {
				visit[*(int*)(current->data)] = 1;
				parent[*(int*)(current->data)] = neighbor;
				dist[*(int*)(current->data)] = dist[neighbor] + 1;
				q_enqueue(q, (int*)(current->data));
			}
			current = current->next;
		}
		visit[neighbor] = 2;
	}
	q_clear(q);
	q_free(q);

	if(dist[dest] == INF) {
		printf("INF");
	} else {
		printf("The min_path from %d to %d is: ", start, dest);
		path[count] = dest;

		while(parent[dest] != -1) {
			count++;
			path[count] = parent[dest];
			dest = parent[dest];
		}

		for(int i = count; i >= 0; i--) {
			printf("%d ", path[i]);
		}
	}
}

static int
bfs_check_bipartite(list_graph_t* lg, int node, int* color) {

	queue_t *q = q_create(sizeof(int), MAX_NODES);
	color[node] = 1;
	q_enqueue(q, &node);

	while(!q_is_empty(q)) {
		int neighbor = *(int*)q_front(q);
		q_dequeue(q);

		ll_node_t* current = lg->neighbors[neighbor]->head;

		while(current) {
			if(color[*(int*)(current->data)] == color[neighbor]) {
				q_clear(q);
				q_free(q);
				return 0;
			}
			if(color[*(int*)(current->data)] == 0) {
				if(color[neighbor] == 1) {
					color[*(int*)(current->data)] = 2;
				} else
					color[*(int*)(current->data)] = 1;
				q_enqueue(q, (int*)(current->data));
			}
			current = current->next;
		}
	}

	q_clear(q);
	q_free(q);
	return 1;
}

static int
check_bipartite(list_graph_t *lg, int *color)
{
	/* TODO: multimile vor avea culorile 1, respectiv 2 */
	int count_bipartite;
	for(int i = 0; i < lg->nodes; i++) {
		color[i] = 0;
	}

	for(int j = 0; j < lg->nodes; j++) {
		if(color[j] == 0) {
			count_bipartite = bfs_check_bipartite(lg, j, color);
		}
	}

	if(count_bipartite == 0) {
		return 0;
	}
 	return 1;
}

static void
test_connected_comp(void)
{
	unsigned int num_comps = 0, i, nodes, edges;
	int x, y;
	int visited[MAX_NODES] = {0};
	list_graph_t *lg;
	linked_list_t **comps;

	printf("UNDIRECTED graph for the connected components problem:\n");
	scanf("%u %u", &nodes, &edges);
	lg = lg_create(nodes);

	for (i = 0; i != edges; ++i) {
		scanf("%d %d", &x, &y);
		lg_add_edge(lg, x, y);
		lg_add_edge(lg, y, x);
	}

	comps = connected_components(lg, visited, &num_comps);

	printf("Found %u connected components:\n", num_comps);
	for (i = 0; i != num_comps; ++i) {
		ll_print_int(comps[i]);
		ll_free(comps + i);
	}
	printf("\n");

	free(comps);
	lg_free(lg);
}

static void
test_topo_sort(void)
{
	unsigned int i, nodes, edges;
	int x, y;
	int visited[MAX_NODES] = {0};
	list_graph_t *lg;
	linked_list_t *sorted;

	printf("DIRECTED graph for the topological sort problem:\n");
	scanf("%u %u", &nodes, &edges);
	lg = lg_create(nodes);

	for (i = 0; i != edges; ++i) {
		scanf("%d %d", &x, &y);
		lg_add_edge(lg, x, y);
	}

	sorted = topo_sort(lg, visited);

	printf("Topologically sorted nodes:\n");
	ll_print_int(sorted);
	printf("\n");

	ll_free(&sorted);
	lg_free(lg);
}

static void
test_min_dist(void)
{
	unsigned int i, nodes, edges;
	int x, y;
	int dist[MAX_NODES] = {0};
	list_graph_t *lg;

	printf("UNDIRECTED graph for the minimum distance problem:\n");
	scanf("%u %u", &nodes, &edges);
	lg = lg_create(nodes);

	for (i = 0; i != edges; ++i) {
		scanf("%d %d", &x, &y);
		lg_add_edge(lg, x, y);
		lg_add_edge(lg, y, x);
	}

	for (i = 0; i != nodes; ++i)
		dist[i] = INF;

	min_path(lg, 0, dist);

	printf("\nMinimum distances to node 0:\n");
	for (i = 0; i != nodes; ++i)
		printf("%u: %d\n", i, dist[i]);
	printf("\n");

	lg_free(lg);
}

static void
test_bipartite(void)
{
	unsigned int i, nodes, edges;
	int color[MAX_NODES] = {0};
	int x, y;
	list_graph_t *lg;

	printf("UNDIRECTED graph for the bipartite graph problem:\n");
	scanf("%u %u", &nodes, &edges);
	lg = lg_create(nodes);

	for (i = 0; i != edges; ++i) {
		scanf("%d %d", &x, &y);
		lg_add_edge(lg, x, y);
		lg_add_edge(lg, y, x);
	}
	
	if (check_bipartite(lg, color)) {
		printf("Nodes with colour 1:\n");
		for (int i = 0; i < lg->nodes; ++i)
			if (color[i] == 1)
				printf("%d ", i);
		printf("\nNodes with colour 2:\n");
		for (int i = 0; i < lg->nodes; ++i)
			if (color[i] == 2)
				printf("%d ", i);
		printf("\n");
	} else
		printf("The graph is not bipartite\n");

	lg_free(lg);
}

int
main(void)
{
	/* Ex 1 */
	test_connected_comp();

	/* Ex 2 */
	test_topo_sort();

	/* Ex 3 */
	test_min_dist();
	/*
		INPUT : 7 10
			    0  1
			    0  4
			    1  2
			    1  3
			    1  4
			    2  4
			    3  5
			    3  6
			    4  5
			    4  6
			    the dest node : 6
	*/


	/* Ex 4 */
	test_bipartite();

	return 0;
}
