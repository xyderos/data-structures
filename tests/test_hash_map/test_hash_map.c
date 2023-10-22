#include "test_hash_map.h"

Suite *
table_suite(void)
{
	Suite *s = NULL;
	TCase *tc_core = NULL;

	s = suite_create("hash_map");
	tc_core = tcase_create("core");

	tcase_add_test(tc_core, TEST_INSERTING_ITEM_SHOULD_BE_OKAY);
	tcase_add_test(tc_core, TEST_GETTING_ITEM_SHOULD_BE_OKAY);
	tcase_add_test(tc_core, TEST_INSERTING_AND_RESIZING_SHOULD_BE_OKAY);
	tcase_add_test(tc_core, TEST_INSERTING_DUPLICATE_KEYS_SHOULD_BE_OKAY);

	suite_add_tcase(s, tc_core);

	return s;
}
