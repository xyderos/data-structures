#include "test_dictionary.h"

Suite *
dictionary_suite(void)
{
	Suite *s = NULL;
	TCase *tc_core = NULL;

	s = suite_create("dictionary");
	tc_core = tcase_create("core");

	tcase_add_test(tc_core, INITIALIZE_VOCABULARY_FROM_FILE_SHOULD_BE_OKAY);
	tcase_add_test(tc_core, REPAIR_SENTENCE_SHOULD_BE_OKAY);

	suite_add_tcase(s, tc_core);

	return s;
}
