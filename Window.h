#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>

class Window
{
	public:
		Window() = default;
		Window(Window&) = default;
		Window& operator=(Window&) = default;
		Window(char* window_title, const unsigned & window_width, const unsigned & window_height);
		
		int getWidth();
		int getHeight();
		
		void free();
		
		SDL_Surface* getSurface();
		SDL_Renderer* getRenderer() { return renderer_; };
	private:
		void update();
		SDL_Window* window_{};
		SDL_Renderer* renderer_{};
};

#endif