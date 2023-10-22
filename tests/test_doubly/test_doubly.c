#include "test_doubly.h"

Suite *
doubly_linked_list_suite(void)
{
	Suite *s = NULL;
	TCase *tc_core = NULL;

	s = suite_create("doubly_linked_list");
	tc_core = tcase_create("core");

	tcase_add_test(tc_core,
	    TEST_DOUBLY_LINKED_LIST_SHOULD_DELETE_FROM_THE_FRONT);
	tcase_add_test(tc_core,
	    TEST_DOUBLY_LINKED_LIST_SHOULD_DELETE_FROM_THE_BACK);
	tcase_add_test(tc_core,
	    TEST_DOUBLY_LINKED_LIST_SHOULD_INSERT_FROM_THE_FRONT);
	tcase_add_test(tc_core,
	    TEST_DOUBLY_LINKED_LIST_SHOULD_INSERT_FROM_THE_BACK);

	suite_add_tcase(s, tc_core);

	return s;
}
