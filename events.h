#ifndef EVENTS_H
#define EVENTS_H

#define NUMBER_OF_EVENTS 322
#define FRAMES_UNTIL_KEY_IS_DEFINED_AS_PRESSED 10

typedef enum{
	UP,
	DOWN,
	KEY_PRESS
}KEY_STATE;

#include <SDL.h>


typedef struct {
	int state; //the state of the key, is it up, down or preesed
	int number_of_frames; //how many frames the key is held
}clicked_keys; //always one in game


clicked_keys* get_keyboard_events();
void update_key_frames_and_states(clicked_keys* keys);

#endif 
