#pragma once

#include <stddef.h>

typedef struct hash_map_entry {

	char *key;

	char *value;

} hash_map_entry_t;

typedef struct hash_map_table {

	size_t size;

	size_t used_entries;

	hash_map_entry_t **entries;

	size_t seed;

} hash_map_table_t;

hash_map_table_t *table_init(const size_t);

size_t table_insert(hash_map_table_t *, const char *const, const char *const);

const char *table_get(const hash_map_table_t *const, const char *const);

void table_destroy(hash_map_table_t *);
