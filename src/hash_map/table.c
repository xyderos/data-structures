#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../hash/hash.h"
#include "table.h"

static hash_map_entry_t *
entry_init(const char *const key, const char *const value)
{
	hash_map_entry_t *entry = malloc(sizeof(hash_map_entry_t));

	if (!entry) {
		return NULL;
	}

	entry->key = strdup(key);
	entry->value = strdup(value);

	return entry;
}

static void
entry_delete(hash_map_entry_t *entry)
{
	free(entry->key);
	free(entry->value);
	free(entry);
}

hash_map_table_t *
table_init(const size_t size)
{
	hash_map_table_t *table = malloc(sizeof(hash_map_table_t));

	if (!table) {
		return NULL;
	}

	table->entries = calloc((size_t)size, sizeof(hash_map_entry_t *));
	table->size = size;
	table->used_entries = 0;
	table->seed = get_prime();

	return table;
}

void
table_destroy(hash_map_table_t *table)
{
	hash_map_entry_t *iterator = NULL;

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
table_resize(hash_map_table_t *table, const size_t new_size)
{
	hash_map_entry_t *iterator = NULL;
	size_t current_hash_table_size = table->size;
	hash_map_entry_t **current_entries = table->entries;

	hash_map_table_t *temp = table_init(new_size);

	for (unsigned int index = 0; index < table->size; index++) {
		iterator = table->entries[index];

		if (iterator) {
			table_insert(temp, iterator->key, iterator->value);
		}
	}

	table->entries = temp->entries;

	table->size = temp->size;
	temp->size = current_hash_table_size;

	table->entries = temp->entries;
	temp->entries = current_entries;

	table_destroy(temp);
}

size_t
table_insert(hash_map_table_t *table, const char *const key,
    const char *const value)
{
	hash_map_entry_t *entry = NULL;
	size_t index = 0, position = 0;

	if (table->used_entries > ((table->size * 2) / 3)) {
		table_resize(table, 2 * table->used_entries);
	}

	while (position != table->size) {

		index = hash_string(table->seed, table->size, key, position);

		entry = table->entries[index];

		if (!entry) {
			entry = entry_init(key, value);

			table->entries[index] = entry;

			table->used_entries++;
			return index;
		}

		else if (!strcmp(entry->key, key)) {

			char *to_delete = entry->value;
			free(to_delete);

			entry->value = strdup(value);
			return index;
		}

		position++;
	}
	return INT_MAX;
}

const char *
table_get(const hash_map_table_t *const table, const char *const key)
{
	size_t index = 0;

	hash_map_entry_t *entry = NULL;

	for (size_t iteration = 0; iteration < table->size; ++iteration) {

		index = hash_string(table->seed, table->size, key, iteration);

		entry = table->entries[index];

		if (entry && strcmp(key, entry->key) == 0) {

			return entry->value;
		}
	}
	return NULL;
}
