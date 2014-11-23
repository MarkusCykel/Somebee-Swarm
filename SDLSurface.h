#ifndef SDLSURFACE_H
#define SDLSURFACE_H

#include <SDL.h>
#include <iostream>

#include "SDLWindow.h"

class SDLSurface
{
	public:
		SDLSurface(const SDLWindow &);
		~SDLSurface() = default;
		
		void fill(int);
	private:
		SDL_Surface* surface_;
};

#endif