#ifndef SDLWINDOW_H
#define SDLWINDOW_H

#include "SDLSurface.h"

class SDLWindow
{
	public:
		SDLWindow(char* window_title, const unsigned & window_width, const unsigned & window_height);
		~SDLWindow() {	SDL_DestroyWindow(window_); };
		
		void fill(const unsigned &,const unsigned &,const unsigned &);
		void blitSurface(const SDLSurface& surface);
		void blitSurface(const SDLSurface& surface,const unsigned &,const unsigned &);
		SDL_PixelFormat* get_format() { return surface_.get_format(); };
	private:
		void update();
		SDL_Window* window_;
		SDLSurface surface_;
};

#endif