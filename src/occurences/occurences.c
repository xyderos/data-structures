#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "occurences.h"

static const char *const DELIMS =
    ",  \" . ! ?  @ $ % ^ & * ; 1 2 3 4 5 6 7 8 9 0 ( ) / - '  = _ ~ ` > < : # + ";

enum { INITIAL_SIZE = 1024 };

static int
check_string(const char *s)
{
	for (unsigned int i = 0; i != strlen(s); i++) {

		if (!isalpha(s[i])) {
			return 0;
		}
	}

	return 1;
}

occurence_map_t *
initialize_grid(const char *const file_name)
{
	FILE *fp = fopen(file_name, "r");
	occurence_map_t *grid = NULL;

	char *buffer = NULL, *token = NULL;
	size_t len = 0;
	long read = 0;

	if (!fp) {
		return NULL;
	}

	grid = occurence_map_init(INITIAL_SIZE);

	while ((read = getline(&buffer, &len, fp)) != -1) {

		token = strtok(buffer, DELIMS);

		while (token != NULL) {

			if (check_string(token)) {
				occurence_map_insert(grid, token);
			}

			token = strtok(NULL, DELIMS);
		}
	}

	(void)fclose(fp);

	free(buffer);

	occurence_map_sort(grid);

	return grid;
}

const char *
nth(const occurence_map_t *const table, const unsigned int position)
{
	return table->entries[position]->value;
}

const char **
from_nth_to_kth(const occurence_map_t *table, const unsigned int start,
    const unsigned int finish)
{
	unsigned pos = 0;
	const char **result = malloc(sizeof(char *) * (finish - start));

	for (unsigned int index = start; index != finish; index++) {
		result[pos++] = table->entries[index]->value;
	}

	return result;
}
