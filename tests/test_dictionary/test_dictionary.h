#include <check.h>
#include <stdlib.h>

#include "../../src/dictionary/dictionary.h"

Suite *dictionary_suite(void);

START_TEST(INITIALIZE_VOCABULARY_FROM_FILE_SHOULD_BE_OKAY)
{
	const char *result = NULL;
	hash_map_table_t *table = initialize_vocabulary("data/misspellings");

	if (!table) {
		return;
	}

	result = table_get(table, "wirting");

	ck_assert_pstr_eq(result, "writing");

	table_destroy(table);
}
END_TEST

START_TEST(REPAIR_SENTENCE_SHOULD_BE_OKAY)
{
	hash_map_table_t *table = initialize_vocabulary("data/misspellings");
	char *res = repair_sentence(table, "abandonned child");

	ck_assert_pstr_eq(res, "abandoned child");

	free(res);

	table_destroy(table);
}
END_TEST
