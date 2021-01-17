#ifndef EVENTS_HANDLER_H
#define EVENTS_HANDLER_H

#define MAX_EVENTS 64

typedef struct Event
{
	char* event_name;
	int event_number;
};


Event* create_events_chain();
Event* get_events();

#endif

