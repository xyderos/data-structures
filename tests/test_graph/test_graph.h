#include <check.h>
#include <limits.h>
#include <stdio.h>

#include "../../src/graph/graph.h"

Suite *graph_suite(void);

START_TEST(INITIALIZING_A_GRAPH_SHOULD_BE_OKAY)
{
	graph_t *graph = graph_initialize("data/undirected");

	ck_assert_ptr_nonnull(graph);

	graph_destroy(graph);
}
END_TEST
