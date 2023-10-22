#include "test_graph.h"

Suite *
graph_suite(void)
{
	Suite *s = NULL;
	TCase *tc_core = NULL;

	s = suite_create("graph");
	tc_core = tcase_create("core");

	tcase_add_test(tc_core, INITIALIZING_A_GRAPH_SHOULD_BE_OKAY);

	suite_add_tcase(s, tc_core);

	return s;
}
