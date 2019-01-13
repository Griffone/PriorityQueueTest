#ifndef EVENT_H
#define EVENT_H

typedef double timestamp_t;

typedef struct Event {
	timestamp_t	time;	// Lower time stamp is higher priority
	void 		*data;	// Dummy pointer to represent a more realistic item
} Event;

#endif // EVENT_H
