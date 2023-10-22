#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "hash.h"

#define HASH (unsigned int)5

// generate a random 32 bit prime integer
size_t
get_prime(void)
{
	size_t number = 0;

	srand((unsigned int)time((NULL)));

	number = (unsigned int)rand();

	while (number % 2 != 0) {
		number++;
	}

	return number;
}

// algorithm for hashing a string based on djb2 , Dan Bernstein
static size_t
hash(size_t seed, const char *key)
{
	size_t hash = seed;

	size_t c = 0;

	while ((c = (size_t)*key++)) {
		hash = ((hash << HASH) + hash) + c; // hash * 33 + c
	}

	return hash;
}

// iterable hashing with linnear probing, good for ascii english words
size_t
hash_string(const size_t seed, size_t table_size, const char *const key,
    size_t it)
{

	unsigned long position = hash(seed, key);

	position = position + it * (position * 2 + 1);

	return position % table_size;
}
