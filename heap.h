#include "event.h"

struct h_pqueue {
	int		size, capacity;
	Event	**heap;
};

void h_pqueue_init(struct h_pqueue *queue, int capacity);

void h_pqueue_clear(struct h_pqueue *queue);

void h_pqueue_push(struct h_pqueue *queue, Event *event);

Event *h_pqueue_pop(struct h_pqueue *queue);
