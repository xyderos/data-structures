#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../hash_map/table.h"

hash_map_table_t *initialize_vocabulary(const char *const);

char *repair_sentence(const hash_map_table_t *const, char *);
