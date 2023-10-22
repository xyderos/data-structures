#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

#define INITIAL_SIZE 1024

static const char *const DELIMS = ", -> > \n";

hash_map_table_t *
initialize_vocabulary(const char *const file_name)
{
	char *line = NULL, *misspelled_word = NULL, *correct_word = NULL;

	FILE *fp = NULL;

	unsigned long len = 0;

	long read = 0;

	hash_map_table_t *table = table_init(INITIAL_SIZE);

	fp = fopen(file_name, "r");

	if (!fp) {
		return NULL;
	}

	while ((read = getline(&line, &len, fp)) != -1) {

		misspelled_word = strtok(line, DELIMS);
		correct_word = strtok(NULL, DELIMS);

		table_insert(table, misspelled_word, correct_word);
	}

	fclose(fp);

	free(line);

	return table;
}

static inline char *
append(char *sentence_accumulator, char *word_accumulator)
{
	size_t s1 = strlen(sentence_accumulator);
	size_t s2 = strlen(word_accumulator);
	char *result = NULL;
	result = calloc((s1 + s2 + 2), sizeof(char));

	strcat(result, sentence_accumulator);

	if (strlen(result) == 0) {
		goto not_initialized;
	}

	strcat(result, " ");

not_initialized:

	strcat(result, word_accumulator);

	result[s1 + s2 + 1] = '\0';
	return result;
}

char *
repair_sentence(const hash_map_table_t *const table, char *sentence)
{
	const char *to_be_deleted = NULL, *correct_word = NULL,
		   *w_accumulator = NULL, *s_accunulator = "",
		   *copy = strdup(sentence);
	int success = -1;

	w_accumulator = strtok(copy, DELIMS);

	success = w_accumulator != NULL;

	while (success) {

		correct_word = table_get(table, w_accumulator);

		if (correct_word) {
			w_accumulator = correct_word;
		}

		to_be_deleted = s_accunulator;

		s_accunulator = append(s_accunulator, w_accumulator);

		if (strcmp(to_be_deleted, "") != 0) {
			free(to_be_deleted);
		}

		w_accumulator = strtok(NULL, DELIMS);

		success = w_accumulator != NULL;
	}

	free(copy);

	return s_accunulator;
}
