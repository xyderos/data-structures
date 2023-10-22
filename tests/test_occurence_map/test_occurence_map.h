#include <check.h>
#include <limits.h>

#include "../../src/occurence_map/table.h"

Suite *map_suite(void);

START_TEST(MAP_TEST_INSERTING_ITEM_SHOULD_BE_OKAY)
{
	size_t index = 0;
	occurence_map_t *table = occurence_map_init(3);

	index = occurence_map_insert(table, "kostas");

	ck_assert_int_ne(index, INT_MAX);
	ck_assert_int_ne(index, 0);

	occurence_map_destroy(table);
}
END_TEST

START_TEST(MAP_TEST_GETTING_ITEM_SHOULD_BE_OKAY)
{
	unsigned long occurence = 0;
	occurence_map_t *table = occurence_map_init(3);

	occurence_map_insert(table, "kostas");

	occurence = occurence_map_get(table, "kostas");

	ck_assert_int_eq(occurence, 1);

	occurence_map_destroy(table);
}
END_TEST

START_TEST(MAP_TEST_INSERTING_AND_RESIZING_SHOULD_BE_OKAY)
{
	unsigned long occurence = 0;
	occurence_map_t *table = occurence_map_init(3);

	occurence_map_insert(table, "kostas");
	occurence_map_insert(table, "konstantinos");
	occurence_map_insert(table, "kostis");

	occurence = occurence_map_get(table, "kostas");

	ck_assert_int_eq(occurence, 1);

	occurence_map_destroy(table);
}
END_TEST

START_TEST(MAP_TEST_INSERTING_DUPLICATE_KEYS_SHOULD_BE_OKAY)
{
	unsigned long occurence = 0;
	occurence_map_t *table = occurence_map_init(3);

	occurence_map_insert(table, "kostas");
	occurence_map_insert(table, "kostas");

	occurence = occurence_map_get(table, "kostas");

	ck_assert_int_eq(occurence, 2);

	occurence_map_destroy(table);
}
END_TEST

START_TEST(TEST_SORTING_TABLE_SHOULD_BE_OKAY)
{
	occurence_map_t *table = occurence_map_init(4);

	occurence_map_insert(table, "a");
	occurence_map_insert(table, "a");
	occurence_map_insert(table, "a");
	occurence_map_insert(table, "a");
	occurence_map_insert(table, "c");
	occurence_map_insert(table, "c");
	occurence_map_insert(table, "c");
	occurence_map_insert(table, "d");
	occurence_map_insert(table, "d");
	occurence_map_insert(table, "b");

	occurence_map_sort(table);

	for (unsigned int index = 0; index != 4; index++) {
		if (index == 0) {
			ck_assert_pstr_eq(table->entries[index]->value, "a");
		} else if (index == 1) {
			ck_assert_pstr_eq(table->entries[index]->value, "c");
		} else if (index == 2) {
			ck_assert_pstr_eq(table->entries[index]->value, "d");
		} else if (index == 3) {
			ck_assert_pstr_eq(table->entries[index]->value, "b");
		}
	}
	occurence_map_destroy(table);
}
END_TEST
