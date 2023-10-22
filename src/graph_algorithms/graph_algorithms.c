#include <stdlib.h>

#include "../queue/queue.h"
#include "graph_algorithms.h"

int
has_been_visited(int *haystack, int needle)
{
	int *x = haystack;

	while (*x != '\0') {
		if (*x == needle) {
			return 1;
		}
		x++;
	}
	return 0;
}

void
free_path(int *path)
{
	free(path);
}