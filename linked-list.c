#include "linked-list.h"

#ifndef NULL
#define NULL 0
#endif // NULL

#include <stdlib.h>

static inline void * alloc_mem(int size) {
	return malloc(size);
}

static inline void * free_mem(void *item) {
	free(item);
}

typedef struct ll_pqueue pqueue_t;
typedef struct ll_item {
	Event 			*event;
	struct ll_item	*next;
} item_t;

void ll_pqueue_init(pqueue_t *queue) {
	queue->first = NULL;
}

void ll_pqueue_push(pqueue_t *queue, Event *event) {
	item_t *item = alloc_mem(sizeof(item_t));
	item->event = event;
	
	if ((item_t *)queue->first == NULL) {
		queue->first = item;
		return;
	}
	
	if (((item_t *)queue->first)->event->time > event->time) {
		item->next = (item_t*)queue->first;
		queue->first = item;
		return;
	}
	
	item_t *prev = (item_t *)queue->first;
	item_t *next = prev->next;
	
	while (next != NULL) {
		if (event->time < next->event->time) break;
		
		prev = next;
		next = next->next;
	}
	
	prev->next = item;
	item->next = next;
}

Event* ll_pqueue_pop(pqueue_t *queue) {
	if (queue->first == NULL) return NULL;
	
	item_t *item = (item_t *)queue->first;
	queue->first = item->next;
	
	Event *event = item->event;
	free_mem(item);
	return event;
}
