#include "linked-list.h"
#include "heap.h"

#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define ITEM_COUNT	100000

#define TU_PER_SEC		1000
#define NANOS_PER_TU	(1000000000 / TU_PER_SEC)


static char const * const TIME_UNIT = "ms";


void run_test(void *queue, void (*enqueue)(void *q, Event*e), Event *(*dequeue)(void *q));


static Event events[ITEM_COUNT];


static inline double get_time_since(struct timespec *time) {
	struct timespec now;
	clock_gettime(CLOCK_MONOTONIC, &now);
	double seconds = now.tv_sec - time->tv_sec;
	long nanos = (now.tv_nsec + (1000000000 - time->tv_nsec)) % 1000000000;
	return seconds * TU_PER_SEC + (double) nanos / NANOS_PER_TU;
}

Event gen_event() {
	Event event = {
		(timestamp_t)rand() / (timestamp_t)RAND_MAX,
		NULL
	};
	return event;
}


void ll_enqueue(void *queue, Event *event) {
	ll_pqueue_push((struct ll_pqueue *)queue, event);
}

Event *ll_dequeue(void *queue) {
	return ll_pqueue_pop((struct ll_pqueue *)queue);
}

void h_enqueue(void *queue, Event *event) {
	h_pqueue_push((struct h_pqueue *)queue, event);
}

Event *h_dequeue(void *queue) {
	return h_pqueue_pop((struct h_pqueue *)queue);
}


int main() {
	srand(time(NULL));
	for (int i = 0; i < ITEM_COUNT; ++i)
		events[i] = gen_event();
	
	struct timespec start_time;
	double time;
	
	struct ll_pqueue ll_queue;
	ll_pqueue_init(&ll_queue);
	
	printf("Running test for linked-list\n");
	clock_gettime(CLOCK_MONOTONIC, &start_time);
	run_test(&ll_queue, &ll_enqueue, &ll_dequeue);
	time = get_time_since(&start_time);
	
	printf("Linked-list test ran for %.2f%s\n", time, TIME_UNIT);
	
	struct h_pqueue h_queue;
	h_pqueue_init(&h_queue, ITEM_COUNT);
	
	printf("Running test for heap\n");
	clock_gettime(CLOCK_MONOTONIC, &start_time);
	run_test(&h_queue, &h_enqueue, &h_dequeue);
	time = get_time_since(&start_time);
	printf("Heap test ran for %.2f%s\n", time, TIME_UNIT);
	
	h_pqueue_clear(&h_queue);
}

void run_test(void *queue, void (*enqueue)(void *q, Event *e), Event *(*dequeue)(void *q)) {
	for (int i = 0; i < ITEM_COUNT; ++i)
		enqueue(queue, &events[i]);
	
	Event *last = dequeue(queue);
	for (int i = 1; i < ITEM_COUNT; ++i) {
		Event *event = dequeue(queue);
		assert(event->time >= last->time);
		last = event;
	}
}
