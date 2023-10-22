#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../occurence_map/table.h"

const char *nth(const occurence_map_t *const, const unsigned int);

const char **from_nth_to_kth(const occurence_map_t *, const unsigned int,
    const unsigned int);

occurence_map_t *initialize_grid(const char *const);
