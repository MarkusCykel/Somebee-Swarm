#ifndef HARDWARE_INPUT_H
#define HARDWARE_INPUT_H

#include <SDL.h>

class Hardware_Input
{
	public:
		const Uint8* get_keyState() { return SDL_GetKeyboardState(NULL); }
		
		
	private:
		SDL_Event e;
}

#endif