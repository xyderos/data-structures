#include <check.h>
#include <limits.h>

#include "../../src/hash_map/table.h"

Suite *table_suite(void);

START_TEST(TEST_INSERTING_ITEM_SHOULD_BE_OKAY)
{
	size_t index = 0;
	hash_map_table_t *table = table_init(3);

	index = table_insert(table, "kostas", "kostas");

	ck_assert_int_ne(index, INT_MAX);
	ck_assert_int_ne(index, 0);

	table_destroy(table);
}
END_TEST

START_TEST(TEST_GETTING_ITEM_SHOULD_BE_OKAY)
{
	const char *result = NULL;
	hash_map_table_t *table = table_init(3);

	table_insert(table, "kostas", "kostas");

	result = table_get(table, "kostas");

	ck_assert_pstr_eq(result, "kostas");

	table_destroy(table);
}
END_TEST

START_TEST(TEST_INSERTING_AND_RESIZING_SHOULD_BE_OKAY)
{
	const char *result = NULL;
	hash_map_table_t *table = table_init(3);

	table_insert(table, "kostas", "kostas");
	table_insert(table, "konstantinos", "kostas");
	table_insert(table, "kostis", "kostas");

	result = table_get(table, "kostas");

	ck_assert_pstr_eq(result, "kostas");

	table_destroy(table);
}
END_TEST

START_TEST(TEST_INSERTING_DUPLICATE_KEYS_SHOULD_BE_OKAY)
{
	const char *result = NULL;
	hash_map_table_t *table = table_init(3);

	table_insert(table, "kostas", "kostas");
	table_insert(table, "kostas", "konstantinos");

	result = table_get(table, "kostas");

	ck_assert_pstr_eq(result, "konstantinos");

	table_destroy(table);
}
END_TEST
