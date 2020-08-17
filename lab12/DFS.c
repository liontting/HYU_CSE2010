#include <stdio.h>
#define MAX_VERTICES 4

typedef struct graph
{
	int node;
	struct graph *link;
} list;
list *adj_list[MAX_VERTICES];

int adj_mat[MAX_VERTICES][MAX_VERTICES] = {
	{0, 1, 0, 1},
	{1, 0, 1, 1},
	{0, 1, 0, 1},
	{1, 1, 1, 0}};
int visited[MAX_VERTICES];
int n = 4;

void graph_dfs_mat(int v)
{
	int w;
	visited[v] = 1;
	printf("%d ", v);

	for (w = 0; w < n; w++) {
		if (adj_mat[v][w] && !visited[w])
			graph_dfs_mat(w);
	}
}

int main()
{
	graph_dfs_mat(0);
	return 0;
}