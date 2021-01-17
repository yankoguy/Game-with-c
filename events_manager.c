#include "stdafx.h"
#include "events.h"
#include <SDL.h>


clicked_keys* get_keyboard_events() {
	static clicked_keys KEYS[NUMBER_OF_EVENTS];
	// message processing loop
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		// check for messages
		switch (event.type) {

		case SDL_KEYDOWN:
			KEYS[event.key.keysym.sym].state = DOWN;	
			break;
		case SDL_KEYUP:
			KEYS[event.key.keysym.sym].state = UP;
			KEYS[event.key.keysym.sym].number_of_frames = 0;
			break;
		default:
			break;
		}
	}
	update_key_frames_and_states(KEYS);
	return KEYS;
}

void update_key_frames_and_states(clicked_keys* keys) {
	for (int i = 0; i < NUMBER_OF_EVENTS; i++)
	{
		if (keys[i].state == DOWN && keys[i].number_of_frames == FRAMES_UNTIL_KEY_IS_DEFINED_AS_PRESSED) {
			keys[i].state = KEY_PRESS;
		}
		if (keys[i].state == DOWN) {
			keys[i].number_of_frames += 1;
		}
	}
}