#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../hash/hash.h"
#include "table.h"

static occurence_map_entry_t *
entry_init(const char *const value)
{
	occurence_map_entry_t *entry = malloc(sizeof(occurence_map_entry_t));

	if (!entry) {
		return NULL;
	}

	entry->value = strdup(value);
	entry->occurence = 1;

	return entry;
}

static void
entry_delete(occurence_map_entry_t *entry)
{
	free(entry->value);
	free(entry);
}

occurence_map_t *
occurence_map_init(const size_t size)
{
	occurence_map_t *table = malloc(sizeof(occurence_map_t));

	if (!table) {
		return NULL;
	}

	table->entries = calloc((size_t)size, sizeof(occurence_map_entry_t *));
	table->size = size;
	table->used_entries = 0;
	table->seed = get_prime();

	return table;
}

void
occurence_map_destroy(occurence_map_t *table)
{
	occurence_map_entry_t *iterator = NULL;

	for (unsigned int index = 0; index < table->size; index++) {

		iterator = table->entries[index];

		if (iterator) {
			entry_delete(iterator);
		}
	}

	free(table->entries);
	free(table);
}

static void
occurence_map_resize(occurence_map_t *table, const size_t new_size)
{
	occurence_map_entry_t *iterator = NULL;
	size_t current_hash_table_size = table->size, pos = 0;
	occurence_map_entry_t **current_entries = table->entries;

	occurence_map_t *temp = occurence_map_init(new_size);

	for (unsigned int index = 0; index < table->size; index++) {
		iterator = table->entries[index];

		if (iterator) {
			pos = occurence_map_insert(temp, iterator->value);

			if (pos == INT_MAX) {
				continue;
			}
			temp->entries[pos]->occurence = iterator->occurence;
		}
	}

	table->entries = temp->entries;

	table->size = temp->size;
	temp->size = current_hash_table_size;

	table->entries = temp->entries;
	temp->entries = current_entries;

	occurence_map_destroy(temp);
}

size_t
occurence_map_insert(occurence_map_t *table, const char *const value)
{
	occurence_map_entry_t *entry = NULL;
	size_t index = 0, position = 0;

	if (table->used_entries > ((table->size * 2) / 3)) {
		occurence_map_resize(table, 2 * table->used_entries);
	}

	while (position != table->size) {

		index = hash_string(table->seed, table->size, value, position);

		entry = table->entries[index];

		if (!entry) {
			entry = entry_init(value);

			table->entries[index] = entry;

			table->used_entries++;
			return index;
		}

		else if (!strcmp(entry->value, value)) {
			table->entries[index]->occurence++;
			return index;
		}

		position++;
	}
	return INT_MAX;
}

unsigned long
occurence_map_get(const occurence_map_t *const table, const char *const value)
{
	size_t index = 0;

	occurence_map_entry_t *entry = NULL;

	for (size_t iteration = 0; iteration < table->size; ++iteration) {

		index = hash_string(table->seed, table->size, value, iteration);

		entry = table->entries[index];

		if (entry && strcmp(value, entry->value) == 0) {

			return entry->occurence;
		}
	}
	return 0;
}

static void
occurence_map_cleanup(occurence_map_t *table)
{
	occurence_map_t *temp = occurence_map_init(table->used_entries);
	occurence_map_entry_t **current_entries = table->entries;
	size_t current_hash_table_size = table->size;
	size_t new_hash_table_entries = 0;

	occurence_map_entry_t *iterator = NULL;

	unsigned int pos = 0, index = 0;

	while (pos != table->size) {

		iterator = table->entries[pos];

		if (iterator) {
			temp->entries[index] = entry_init(iterator->value);
			temp->entries[index]->occurence = iterator->occurence;

			new_hash_table_entries++;

			index++;
		}

		pos++;
	}

	table->size = temp->size;
	temp->size = current_hash_table_size;

	table->entries = temp->entries;
	temp->entries = current_entries;

	table->used_entries = new_hash_table_entries;

	occurence_map_destroy(temp);
}

static int
comp(const void *a, const void *b)
{
	const occurence_map_entry_t **a1 = a;
	const occurence_map_entry_t **b1 = b;
	const occurence_map_entry_t *a4 = *a1;
	const occurence_map_entry_t *b4 = *b1;

	int c1 = (int)b4->occurence, c2 = (int)a4->occurence;
	return c1 - c2;
}

void
occurence_map_sort(occurence_map_t *table)
{
	occurence_map_cleanup(table);

	qsort(table->entries, table->used_entries,
	    sizeof(occurence_map_entry_t *), comp);
}
