#include <stdio.h>
#include <stdlib.h>

#include "ListGraph.h"
#include "MatrixGraph.h"
#include "Stack.h"
#include "Queue.h"

#define MAX_NODES 10
#define WHITE 0
#define GREY 1
#define BLACK 2
#define INF 999

void
print_matrix_graph(matrix_graph_t* mg)
{
	for(int i = 0; i < mg->nodes; i++) {
		for(int j = 0; j < mg->nodes; j++) {
			printf("%d ", mg->matrix[i][j]);
		}
		printf("\n");
	} 
}

void
print_list_graph(list_graph_t* lg)
{
	for(int i = 0; i < lg->nodes; i++) {
		printf("%d : ", i);
		ll_print_int(lg->neighbors[i]);
		printf("\n");
	}
}

void
dfs_initialization( int *visited, int *t_desc, int *t_tin, int nodes) {
	for(int i = 0; i < nodes; i++) {
		visited[i] = WHITE;
		t_desc[i] = 0;
		t_tin[i] = 0;
	}
}

void
dfs_list_graph(list_graph_t* lg,
		int node,
		int* visited,
		int* t_desc,
		int* t_tin)
{
	dfs_initialization(visited, t_desc, t_tin, MAX_NODES);

	stack_t* st = st_create(sizeof(int));

	int count_time = 0, top_node = -1;
	int neighbor;
	t_desc[node] = count_time;
	visited[node] = GREY;

	st_push(st, &node);

	while(!st_is_empty(st)) {
		top_node = *(int*)st_peek(st);
		st_pop(st);

		ll_node_t* current = lg->neighbors[top_node]->head;

		while(current != NULL) {
			if(visited[*(int*)(current->data)] == WHITE) {
				count_time++;
				t_desc[*(int*)(current->data)] = count_time;
				visited[*(int*)(current->data)] = GREY;
				st_push(st, (int*)(current->data));
			}
			current = current->next;
		}
		count_time++;
		t_tin[top_node] = count_time;
		visited[top_node] = BLACK;
	}

	st_clear(st);
	st_free(st);
	free(st);
}

void
dfs_list_graph_recursive(list_graph_t* lg,
		int node,
		int* visited,
		int* t_desc,
		int* t_tin)
{

	static int time = 0;
	t_desc[node] = time;
	visited[node] = GREY;
	time++;

	ll_node_t* current = lg->neighbors[node]->head;

	while(current) {
		int neighbor = *((int*)current->data);
		if(visited[neighbor] == WHITE) {
			dfs_list_graph_recursive(lg, neighbor, visited, t_desc, t_tin);
		}
		current = current->next;
	}

	t_tin[node] = time;
	visited[node] = BLACK;
	time++;

}

void
dfs_matrix_graph(matrix_graph_t* mg,
		 int node,
		 int* visited,
		 int* t_desc,
		 int* t_tin)
{
	static int time = 0;
	t_desc[node] = time;
	visited[node] = GREY;
	time++;

	for(int i = 0; i < mg->nodes; i++) {
		int neighbor = i;
		if(visited[neighbor] == WHITE && mg->matrix[node][i] == 1) {
			dfs_matrix_graph(mg, neighbor, visited, t_desc, t_tin);
		}
	}

	t_tin[node] = time;
	visited[node] = BLACK;
	time++;
}

void
bfs_initialization(int *color, int *parent, int node) {
	for(int i = 0; i < node; i++) {
		color[i] = WHITE;
		parent[i] = -1;
	}
}

void
bfs_list_graph(list_graph_t* lg, int node, int* color, int* parent)
{
	bfs_initialization(color, parent, MAX_NODES);
	queue_t *q = q_create(sizeof(int), MAX_NODES);
	color[node] = GREY;
	q_enqueue(q, &node);

	while(!q_is_empty(q)) {
		int neighbor = *(int*)q_front(q);
		printf("%d ", neighbor);
		q_dequeue(q);
		ll_node_t* current = lg->neighbors[neighbor]->head;

		while(current) {
			if(color[*(int*)(current->data)] == WHITE) {
			color[*(int*)(current->data)] = GREY;
			parent[*(int*)(current->data)] = neighbor;
			q_enqueue(q, (int*)(current->data));
			}
			current = current->next;
		}
		color[neighbor] = BLACK;
	}
	q_clear(q);
	q_free(q);
}

void
bfs_matrix_graph(matrix_graph_t* mg, int node, int* color, int* parent)
{
	queue_t *q = q_create(sizeof(int), MAX_NODES);
	bfs_initialization(color, parent, MAX_NODES);
	color[node] = GREY;

	q_enqueue(q, &node);

	while(!q_is_empty(q)) {
		int neighbor = *(int*)q_front(q);
		printf("%d ",neighbor);
		q_dequeue(q);
		for(int i = 0; i < mg->nodes; i++) {

			if(color[i] == 	WHITE && mg->matrix[neighbor][i] == 1) {
				color[i] = GREY;
				parent[i] = neighbor;
				q_enqueue(q, &i);
			}
		}
		color[neighbor] = BLACK;
	}
	q_clear(q);
	q_free(q);
}

void
floyd_warshall(matrix_graph_t* mg)
{
	int distance[mg->nodes][mg->nodes];

	for(int i = 0; i < mg->nodes; i++) {
		for(int j = 0; j < mg->nodes; j++) {
			scanf("%d", &distance[i][j]);
		}
	}

	for(int i = 0; i < mg->nodes; i++) {
		for(int j = 0; j < mg->nodes; j++) {
			for(int k = 0; k < mg->nodes; k++) {
				int sum = distance[j][i] + distance[i][k];
				if(sum < distance[j][k]) {
					distance[j][k] = sum;
				}
			}
		}
	}

	for(int i = 0; i < mg->nodes; i++) {
		for(int j = 0; j < mg->nodes; j++) {
			if(distance[i][j] == INF)
				printf("INF ");
			else
				printf("%d ", distance[i][j]);
		}
		printf("\n");
	}

}

int
main()
{
	int nodes, edges;
	int x[MAX_NODES], y[MAX_NODES];
	int visited[MAX_NODES], t_dest[MAX_NODES], t_fin[MAX_NODES];
	list_graph_t* lg = lg_create(MAX_NODES);
	matrix_graph_t* mg = mg_create(MAX_NODES);

	int numbers[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	printf("-------------------------------- Test ListGraph "
		"--------------------------------\n");
	/* Test add_edge_list_graph has_edge_list_graph */

	lg_add_edge(lg, numbers[0], numbers[1]);
	lg_add_edge(lg, numbers[3], numbers[2]);

	printf("#1:\nOutput: %d\nOutput asteptat: 1\n",
		lg_has_edge(lg, numbers[0], numbers[1]));

	printf("#2:\nOutput: %d\nOutput asteptat: 1\n",
		lg_has_edge(lg, numbers[3], numbers[2]));

	printf("#3:\nOutput: %d\nOutput asteptat: 0\n",
		lg_has_edge(lg, numbers[2], numbers[4]));

	/* Test remove_edge_list_graph */
	lg_remove_edge(lg, numbers[0], numbers[1]);
	printf("#4:\nOutput: %d\nOutput asteptat: 0\n",
		lg_has_edge(lg, numbers[0], numbers[1]));

	/* Test get_neighbours_list_graph */
	lg_add_edge(lg, numbers[0], numbers[1]);
	lg_add_edge(lg, numbers[0], numbers[2]);
	lg_add_edge(lg, numbers[0], numbers[3]);
	lg_add_edge(lg, numbers[0], numbers[4]);

	linked_list_t* l = lg_get_neighbours(lg, numbers[0]);

	printf("#5:\n");
	printf("Output: ");
	ll_print_int(l);
	printf("Output asteptat: 1 2 3 4\n");

	print_list_graph(lg);

	printf("-------------------------------- Test MatrixGraph "
		"--------------------------------\n");
	/* test add edge_matrix_graph has_edge_matrix_graph */
	mg_add_edge(mg, numbers[0], numbers[1]);
	mg_add_edge(mg, numbers[3], numbers[2]);

	printf("#1:\nOutput: %d\nOutput asteptat: 1\n",
		mg_has_edge(mg, numbers[0], numbers[1]));

	printf("#2:\nOutput: %d\nOutput asteptat: 1\n",
		mg_has_edge(mg, numbers[3], numbers[2]));

	printf("#3:\nOutput: %d\nOutput asteptat: 0\n",
		mg_has_edge(mg, numbers[2], numbers[4]));

	/* test remove_edge_matrix_graph */
	mg_remove_edge(mg, numbers[0], numbers[1]);
	printf("#4:\nOutput: %d\nOutput asteptat: 0\n",
		mg_has_edge(mg, numbers[0], numbers[1]));

	print_matrix_graph(mg);
	lg_free(lg);
	mg_free(mg);

	printf("-------------------------------- Test DFS_ListGraph "
		"----------------------------\n");

	lg = lg_create(MAX_NODES);
	mg = mg_create(MAX_NODES);
	scanf("%d", &edges);

	while(edges != 0) {
		int i = 0;
		scanf("%d %d", &x[i], &y[i]);
		lg_add_edge(lg, x[i], y[i]);
		mg_add_edge(mg, x[i], y[i]);
		i++;
		edges--;
	}

	print_list_graph(lg);

	dfs_list_graph(lg, 0, visited, t_dest, t_fin);
	for(int i = 0; i < MAX_NODES; i++) {
		printf("%d : %d %d\n", i, t_dest[i],t_fin[i]);
	}
	printf("\n");

	dfs_initialization(visited, t_dest, t_fin, MAX_NODES);
	dfs_list_graph_recursive(lg, 0, visited, t_dest, t_fin);

	for(int i = 0; i < MAX_NODES; i++) {
		printf("%d : %d %d\n", i, t_dest[i],t_fin[i]);
	}
	printf("\n");

	printf("-------------------------------- Test DFS_MatrixGraph "
		"--------------------------\n");
	print_matrix_graph(mg);

	dfs_initialization(visited, t_dest, t_fin, MAX_NODES);
	dfs_matrix_graph(mg, 0, visited, t_dest, t_fin);

	for(int i = 0; i < MAX_NODES; i++) {
		printf("%d : %d %d\n", i, t_dest[i],t_fin[i]);
	}

	printf("-------------------------------- Test BFS_ListGraph "
		"--------------------------\n");	

	bfs_list_graph(lg, 0, visited, x);

	printf("\n-------------------------------- Test BFS_MatrixGraph "
		"------------------------\n");
	bfs_matrix_graph(mg, 0, visited, x);



	printf("\n---------------------------- Test FloydWarshall "
		"--------------------------\n");
/* TEST INPUT :
	0 999 5 4 3 10 7 1 98 999
	1 0 999 3 999 7 4 91 9 999
	999 999 0 12 3 4 62 9 4 999
	2 10 999 0 65 32 999 99 21 12
	999 1 999 999 0 12 43 999 999 0
	2 999 5 4 3 0 7 1 98 999
	1 0 999 3 999 7 0 91 9 999
	999 999 0 12 3 4 9 0 4 999
	2 10 999 0 65 32 999 21 0 12
	999 1 999 999 0 12 43 999 999 0
*/
	floyd_warshall(mg);
	lg_free(lg);
	mg_free(mg);

	return 0;
}
