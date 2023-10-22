#include <stdlib.h>

#include "../queue/queue.h"
#include "bfs.h"

path_t *
bfs(graph_t *graph, n_t *start, n_t *finish)
{
	n_t *neighbor = NULL, *node = NULL;
	int visited[graph->nof_nodes + 1], *path = NULL;
	unsigned int visited_index = 0, i = 0, path_index = 0;
	queue_t *queue = NULL;
	path_t *p = NULL;
	visited[0] = '\0';

	path = malloc(graph->nof_nodes + 1);

	queue = queue_initialize((unsigned int)graph->nof_nodes);
	queue_enqueue(queue, start);

	while (!queue_is_empty(queue)) {
		node = (n_t *)queue_dequeue(queue);

		if (!has_been_visited(path, node->label)) {
			path[path_index] = node->label;
			path_index += 1;
		}

		if (node->label == finish->label) {
			path[path_index] = '\0';
			p = malloc(sizeof(path_t));
			p->path = path;
			return p;
		}

		for (; i < node->nof_neighbors; i++) {
			neighbor = node->neighbors[i];

			if (has_been_visited(path, node->label)) {
				continue;
			}

			visited[visited_index] = neighbor->label;
			visited[visited_index + 1] = '\0';
			visited_index += 1;

			queue_enqueue(queue, neighbor);
		}
	}

	queue_destroy(queue);
	return NULL;
}
