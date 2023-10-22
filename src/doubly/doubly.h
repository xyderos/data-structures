#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct n {

	struct n *next, *previous;

	void *data;

} node_t;

typedef struct list {

	node_t *head, *sentinel;

} list_t;

list_t *list_init(void *);

void list_destroy(list_t *);

void list_add_front(list_t *, void *);

void list_add_back(list_t *, void *);

void *list_delete_front(list_t *);

void *list_delete_back(list_t *);
