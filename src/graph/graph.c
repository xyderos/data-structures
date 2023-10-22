#define _GNU_SOURCE
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"

static n_t *
node_initialize(int label)
{
	n_t *node = (n_t *)malloc(sizeof(n_t));
	node->label = label;
	node->nof_neighbors = 0;
	node->neighbors = (n_t **)malloc(node->nof_neighbors * sizeof(n_t *));
	node->weights = (int *)malloc(node->nof_neighbors * sizeof(int));
	return node;
}

static void
connect(n_t *either, n_t *other, int weight)
{
	either->neighbors = (n_t **)realloc(either->neighbors,
	    (either->nof_neighbors + 1) * sizeof(n_t *));
	either->weights = (int *)realloc(either->weights,
	    (either->nof_neighbors + 1) * sizeof(int));
	either->neighbors[either->nof_neighbors] = other;
	either->weights[either->nof_neighbors] = weight;
	either->nof_neighbors += 1;
}

static void
node_connect(n_t *either, n_t *other)
{
	connect(either, other, 0);
	connect(other, either, 0);
}

static void
node_connect_weight(n_t *either, n_t *other, int weight)
{
	connect(either, other, weight);
	connect(other, either, weight);
}

static void
node_add(graph_t *g, n_t *node)
{
	g->nodes = (n_t **)realloc(g->nodes,
	    (g->nof_nodes + 1) * sizeof(n_t *));

	g->nodes[g->nof_nodes] = node;
	g->nof_nodes += 1;
}

static n_t *
node_get(graph_t *g, int label)
{
	unsigned long i = 0;
	n_t *node = NULL;
	for (; i < g->nof_nodes; i++) {
		node = g->nodes[i];
		if (node->label == label) {
			return node;
		}
	}
	return NULL;
}

static void
graph_add_edge(graph_t *g, n_t *either, n_t *other, int weight)
{
	if (weight != 0) {
		node_connect_weight(either, other, weight);
	} else {
		node_connect(either, other);
	}

	if (!node_get(g, either->label)) {
		node_add(g, either);
	}

	if (!node_get(g, other->label)) {
		node_add(g, other);
	}
}

static void
read_graph_from_file(graph_t *g, const char *const filename)
{
	FILE *fp = NULL;
	char *line = NULL;
	size_t len = 0;
	ssize_t read = 0;
	char *pch = NULL;
	int from = 0, to = 0;
	int weight = 0;
	n_t *e = NULL, *o = NULL;

	fp = fopen(filename, "r");
	if (!fp) {
		return;
	}

	while ((read = getline(&line, &len, fp)) != -1) {
		int counter = 0;
		pch = strtok(line, " ");
		from = atoi(pch);
		while (pch) {
			counter++;
			pch = strtok(NULL, " ");

			if (counter == 1) {
				to = atoi(pch);
			} else {
				weight = atoi(pch);
				break;
			}
		}

		e = node_get(g, from);
		o = node_get(g, to);

		if (!e && !o) {
			e = node_initialize(from);
			o = node_initialize(to);
		} else if (e && o) {
		} else if (!e && o) {
			e = node_initialize(from);
		} else if (e && !o) {
			o = node_initialize(to);
		}

		graph_add_edge(g, e, o, weight);
	}

	(void)fclose(fp);
	if (line) {
		free(line);
	}
}

graph_t *
graph_initialize(const char *const filename)
{
	graph_t *graph = (graph_t *)malloc(sizeof(graph_t));
	graph->nof_nodes = 0;
	graph->nodes = (n_t **)malloc(graph->nof_nodes * sizeof(graph_t *));

	read_graph_from_file(graph, filename);
	return graph;
}

void
graph_destroy(graph_t *g)
{
	unsigned long i = 0;
	n_t *it = NULL;
	for (; i < g->nof_nodes; i++) {

		it = g->nodes[i];
		if (g->nodes[i]) {
			free(it->weights);
			free(it->neighbors);
			free(it);
		}
	}

	free(g->nodes);

	free(g);
}
