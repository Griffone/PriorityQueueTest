#include "event.h"

struct ll_pqueue {
	void *first;
};

/// Initialize priority queue
void ll_pqueue_init(struct ll_pqueue *queue);

/// Insert an event into the priority queue
void ll_pqueue_push(struct ll_pqueue *queue, Event *event);

/// Remove and event from the priority queue.
Event* ll_pqueue_pop(struct ll_pqueue *queue);
