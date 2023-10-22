#pragma once

typedef struct queue {
	unsigned long in_index, out_index, memory_size, size;
	void **queue;

} queue_t;

queue_t *queue_initialize(unsigned int);
void queue_enqueue(queue_t *, void *);
void *queue_dequeue(queue_t *);
void queue_destroy(queue_t *);
int queue_is_empty(queue_t *);
int queue_is_full(queue_t *);
unsigned int queue_size(queue_t *);
