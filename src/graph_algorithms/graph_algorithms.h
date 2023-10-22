#pragma once

#include "../graph/graph.h"

typedef struct path {
	int *path;
	double cost;
} path_t;

int has_been_visited(int *, int);

void free_path(int *);
unsigned int is_bipartite(graph_t *);
