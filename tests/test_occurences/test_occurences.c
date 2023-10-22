#include "test_occurences.h"

Suite *
nth_suite(void)
{
	Suite *s = NULL;
	TCase *tc_core = NULL;

	s = suite_create("occurences");
	tc_core = tcase_create("core");

	tcase_add_test(tc_core, INITIALIZE_OCCURENCES_FROM_FILE_SHOULD_BE_OKAY);
	tcase_add_test(tc_core, RANK_WORDS_SHOULD_BE_OKAY);

	suite_add_tcase(s, tc_core);

	return s;
}
