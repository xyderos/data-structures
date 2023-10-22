#pragma once

typedef struct node {
	int label;
	unsigned long nof_neighbors;
	struct node **neighbors;
	int *weights;
} n_t;

typedef struct graph {
	unsigned long nof_nodes;
	n_t **nodes;
} graph_t;

graph_t *graph_initialize(const char *const);

void graph_destroy(graph_t *);
