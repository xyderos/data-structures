#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>

#include "dijkstra.h"

static unsigned long
node_index(graph_t *graph, n_t *node)
{
	unsigned long i = 0;
	n_t *n = NULL;

	for (; i < graph->nof_nodes; i++) {
		n = graph->nodes[i];
		if (n->label == node->label) {
			return i;
		}
	}

	return ULONG_MAX;
}

path_t *
dijkstra(graph_t *graph, n_t *start, n_t *finish)
{
	n_t *neighbor = NULL, *node = NULL, *current = NULL;
	double distances[graph->nof_nodes];
	double alternative = 0, shortest = 0;
	int previous[graph->nof_nodes], visited[graph->nof_nodes],
	    path_indices[graph->nof_nodes];
	unsigned long number_of_visited_nodes = 0, index = 0,
		      shortest_index = 0, path_length = 0, u = 0, i = 0;
	path_t *path = NULL;
	int *result = NULL;

	for (; i < graph->nof_nodes; i++) {
		node = graph->nodes[i];

		if (node->label == start->label) {
			distances[i] = 0;
		} else {
			distances[i] = DBL_MAX;
		}

		previous[i] = -1;
		visited[i] = 0;
	}

	while (number_of_visited_nodes < graph->nof_nodes) {
		shortest = DBL_MAX;
		shortest_index = 0;
		for (i = 0; i < graph->nof_nodes; i++) {
			if (distances[i] < shortest && !visited[i]) {
				shortest_index = i;
				shortest = distances[i];
			}
		}

		current = graph->nodes[shortest_index];
		visited[shortest_index] = 1;
		number_of_visited_nodes += 1;

		if (current == finish && current->label == finish->label) {
			break;
		}

		for (i = 0; i < current->nof_neighbors; i++) {
			neighbor = current->neighbors[i];
			index = node_index(graph, neighbor);
			alternative = distances[shortest_index] +
			    current->weights[i];

			if (distances[index] > alternative) {
				distances[index] = alternative;
				previous[index] = (int)shortest_index;
			}
		}
	}

	u = node_index(graph, finish);
	while (u != ULONG_MAX) {
		path_indices[path_length] = (int)u;
		u = (unsigned long)previous[u];
		path_length += 1;
	}

	path = malloc(sizeof(path_t));
	result = malloc(path_length + 1);
	for (i = 0; i < path_length; i++) {
		index = (unsigned long)path_indices[path_length - i - 1];
		result[i] = graph->nodes[index]->label;
	}
	result[path_length] = '\0';

	i = node_index(graph, finish);
	path->path = result;
	path->cost = distances[i];
	return path;
}
