#include "heap.h"

#include <assert.h>
#include <stdlib.h>

typedef struct h_pqueue queue_t;

static inline void * alloc_mem(int size) {
	return malloc(size);
}

static inline void free_mem(void *data) {
	free(data);
}

static inline int parent(int i) {
	return (i-1)/2;
}

static inline int left(int i) {
	return (2*i + 1);
}

static inline int right(int i) {
	return (2*i + 2);
}

static inline void swap(Event **a, Event **b) {
	Event *c = *a;
	*a = *b;
	*b = c;
}

void h_pqueue_init(queue_t *queue, int capacity) {
	queue->heap = alloc_mem(sizeof(Event *) * capacity);
	queue->size = 0;
	queue->capacity = capacity;
}

void h_pqueue_clear(queue_t *queue) {
	free_mem(queue->heap);
}

void h_pqueue_push(queue_t *queue, Event *event) {
	assert(queue->size < queue->capacity);

	int index = queue->size++;
	queue->heap[index] = event;
	
	while (index != 0 && queue->heap[parent(index)]->time > queue->heap[index]->time) {
		swap(&queue->heap[index], &queue->heap[parent(index)]);
		index = parent(index);
	}
}

void min_heapify(queue_t *queue, int index) {
	int l = left(index);
	int r = right(index);
	int smallest = index;
	if (l < queue->size && queue->heap[l]->time < queue->heap[index]->time)
		smallest = l;
	if (r < queue->size && queue->heap[r]->time < queue->heap[smallest]->time)
		smallest = r;
	
	if (smallest != index) {
		swap(&queue->heap[index], &queue->heap[smallest]);
		min_heapify(queue, smallest);
	}
}

Event *h_pqueue_pop(queue_t *queue) {
	if (queue->size == 0) return NULL;
	
	if (queue->size == 1) {
		queue->size--;
		return queue->heap[0];
	}
	
	Event *root = queue->heap[0];
	queue->heap[0] = queue->heap[--queue->size];
	
	min_heapify(queue, 0);
	
	return root;
}
