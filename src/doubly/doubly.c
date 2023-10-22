#include <stdlib.h>

#include "doubly.h"

static node_t *
node_init(void *d)
{
	node_t *n = malloc(sizeof(node_t));

	n->next = n->previous = NULL;

	n->data = d;

	return n;
}

list_t *
list_init(void *data)
{
	list_t *lst = malloc(sizeof(list_t));

	node_t *n = node_init(data);

	lst->head = n;

	lst->sentinel = n;

	return lst;
}

void
list_add_front(list_t *list, void *data)
{
	node_t *nn = node_init(data);

	nn->next = list->head;

	list->head->previous = nn;

	list->head = nn;
}

void
list_add_back(list_t *list, void *data)
{
	node_t *nn = node_init(data);

	nn->previous = list->sentinel;

	list->sentinel->next = nn;

	list->sentinel = list->sentinel->next;
}

void *
list_delete_front(list_t *list)
{
	node_t *tmp = list->head;

	void *item = tmp->data;

	list->head = tmp->next;

	if (list->head == NULL) {
		list->sentinel = list->head;

	} else {
		list->head->previous = NULL;
	}

	free(tmp);

	return item;
}

void *
list_delete_back(list_t *list)
{
	node_t *tmp = list->sentinel;

	void *data = tmp->data;

	if (list->sentinel == NULL) {
		list->head = list->sentinel;

	} else {
		list->sentinel->next = NULL;
	}

	free(tmp);

	return data;
}

void
list_destroy(list_t *list)
{
	node_t *iterator = list->head;

	while (iterator != list->sentinel) {
		if (iterator->previous) {
			free(iterator->previous);
		}

		iterator = iterator->next;
	}

	free(list->head);

	free(list);
}
