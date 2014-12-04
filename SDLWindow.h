#ifndef SDLWINDOW_H
#define SDLWINDOW_H

#include "SDLSurface.h"

class SDLWindow
{
	public:
		SDLWindow(char* window_title, const unsigned & window_width, const unsigned & window_height);
		~SDLWindow() {	SDL_DestroyWindow(window_); };
		
		
		SDL_Renderer* getRenderer() { return renderer_; };
		void fill(const unsigned &,const unsigned &,const unsigned &);
		void blitSurface(const SDLSurface& surface);
		void blitSurface(const SDLSurface& surface,const unsigned &,const unsigned &);
	private:
		void update();
		SDL_Window* window_;
		SDL_Renderer* renderer_;
};

#endif