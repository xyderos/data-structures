#include <check.h>
#include <stdlib.h>

#include "../../src/occurences/occurences.h"

Suite *nth_suite(void);

START_TEST(INITIALIZE_OCCURENCES_FROM_FILE_SHOULD_BE_OKAY)
{
	const char *result = NULL;
	occurence_map_t *table = initialize_grid("data/data_mid");

	if (!table) {
		return;
	}

	result = nth(table, 0);

	ck_assert_pstr_eq(result, "the");

	occurence_map_destroy(table);
}
END_TEST

START_TEST(RANK_WORDS_SHOULD_BE_OKAY)
{
	occurence_map_t *table = initialize_grid("data/data_mid");
	const char **res = from_nth_to_kth(table, 0, 2);
	ck_assert_pstr_eq(res[0], "the");
	ck_assert_pstr_eq(res[1], "a");

	free(res);

	occurence_map_destroy(table);
}
END_TEST
