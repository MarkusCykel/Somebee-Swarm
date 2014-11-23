#ifndef SDLWINDOW_H
#define SDLWINDOW_H

#include <SDL.h>
#include <iostream>

class SDLWindow
{
	public:
		SDLWindow(char* window_title, const int window_width, const int window_height);
		~SDLWindow() {	SDL_DestroyWindow(window_); };
		
		SDL_Window* get() const { return window_; };
		void update();
	private:
		SDL_Window* window_;
};

#endif