#include <stdlib.h>

#include "queue.h"

queue_t *
queue_initialize(unsigned int size)
{
	queue_t *result = malloc(sizeof(queue_t));

	result->size = size;
	result->memory_size = size + 1;
	result->in_index = result->out_index = 0;
	result->queue = calloc(size, sizeof(void *));

	return result;
}

void
queue_enqueue(queue_t *queue, void *item)
{
	if (queue_is_full(queue)) {
		return;
	}

	queue->queue[queue->in_index] = item;
	queue->in_index = (queue->in_index + 1) % queue->memory_size;
}

void *
queue_dequeue(queue_t *queue)
{
	void *item = NULL;
	if (queue_is_empty(queue)) {
		return NULL;
	}

	item = queue->queue[queue->out_index];
	queue->out_index = (queue->out_index + 1) % queue->memory_size;
	return item;
}

void
queue_destroy(queue_t *queue)
{
	free(queue->queue);
	free(queue);
}

int
queue_is_empty(queue_t *queue)
{
	return queue_size(queue) == 0;
}

int
queue_is_full(queue_t *queue)
{
	return queue_size(queue) == queue->size;
}

unsigned int
queue_size(queue_t *queue)
{
	return (unsigned int)queue->in_index - (unsigned int)queue->out_index;
}
