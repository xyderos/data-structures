#include <check.h>

#include "../../src/doubly/doubly.h"

Suite *doubly_linked_list_suite(void);

static int
determine_size(const list_t *const l)
{
	int acc = 1;

	node_t *iterator = l->head;

	while (iterator != l->sentinel) {
		acc++;

		iterator = iterator->next;
	}

	return acc;
}

START_TEST(TEST_DOUBLY_LINKED_LIST_SHOULD_INSERT_FROM_THE_BACK)
{
	int one = 1, two = 2, sz = 0;
	list_t *list = list_init(&one);

	list_add_back(list, &two);

	sz = determine_size(list);

	ck_assert_int_eq(2, sz);

	list_destroy(list);
}
END_TEST

START_TEST(TEST_DOUBLY_LINKED_LIST_SHOULD_INSERT_FROM_THE_FRONT)
{
	int one = 1, two = 2, sz = 0;
	list_t *list = list_init(&one);

	list_add_front(list, &two);

	sz = determine_size(list);

	ck_assert_int_eq(2, sz);

	list_destroy(list);
}

END_TEST

START_TEST(TEST_DOUBLY_LINKED_LIST_SHOULD_DELETE_FROM_THE_BACK)
{
	int one = 1, two = 2, *result = 0;
	list_t *list = list_init(&one);

	list_add_front(list, &two);

	result = (int *)list_delete_back(list);

	ck_assert_int_eq(*result, 1);

	list_destroy(list);
}
END_TEST

START_TEST(TEST_DOUBLY_LINKED_LIST_SHOULD_DELETE_FROM_THE_FRONT)
{
	int one = 1, two = 2, *result = 0;
	list_t *list = list_init(&one);

	list_add_front(list, &two);

	result = (int *)list_delete_front(list);

	ck_assert_int_eq(*result, 2);

	list_destroy(list);
}
END_TEST
