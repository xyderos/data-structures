#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/graph/graph.h"
#include "driver.h"
#include "test_dictionary/test_dictionary.h"
#include "test_doubly/test_doubly.h"
#include "test_graph/test_graph.h"
#include "test_hash_map/test_hash_map.h"
#include "test_occurence_map/test_occurence_map.h"
#include "test_occurences/test_occurences.h"

int
main(void)
{

	int no_failed = 0;
	Suite *s = NULL;
	SRunner *runner = NULL;

	s = nth_suite();
	runner = srunner_create(s);
	srunner_add_suite(runner, map_suite());
	srunner_add_suite(runner, table_suite());
	srunner_add_suite(runner, doubly_linked_list_suite());
	srunner_add_suite(runner, dictionary_suite());
	srunner_add_suite(runner, graph_suite());

	srunner_run_all(runner, CK_NORMAL);
	no_failed = srunner_ntests_failed(runner);
	srunner_free(runner);

	return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
