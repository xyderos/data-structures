#pragma once

#include <stddef.h>

typedef struct occurence_map_entry {

	char *value;

	unsigned long occurence;

} occurence_map_entry_t;

typedef struct occurence_map {

	size_t size;

	size_t used_entries;

	occurence_map_entry_t **entries;

	size_t seed;

} occurence_map_t;

occurence_map_t *occurence_map_init(const size_t);

size_t occurence_map_insert(occurence_map_t *, const char *const);

unsigned long occurence_map_get(const occurence_map_t *const,
    const char *const);

void occurence_map_destroy(occurence_map_t *);

void occurence_map_sort(occurence_map_t *);
