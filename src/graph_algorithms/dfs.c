#include "dfs.h"
#include "stdlib.h"

static path_t *
dfs_internal(graph_t *graph, n_t *start, n_t *finish, int *path,
    unsigned int index)
{
	unsigned int i = 0;
	path_t *p = NULL, *new_path = NULL;

	path[index] = start->label;
	path[index + 1] = '\0';

	if (start->label == finish->label) {
		p = malloc(sizeof(path_t));
		p->path = path;
		return p;
	}

	for (; i < start->nof_neighbors; i++) {
		n_t *node = start->neighbors[i];
		if (has_been_visited(path, node->label)) {
			continue;
		}

		new_path = dfs_internal(graph, node, finish, path, index + 1);
		if (new_path) {
			return new_path;
		}
	}
	free(path);
	return NULL;
}

path_t *
dfs(graph_t *graph, n_t *start, n_t *finish)
{
	int *path = malloc(graph->nof_nodes + 1);
	return dfs_internal(graph, start, finish, path, 0);
}
