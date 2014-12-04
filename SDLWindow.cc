#include <SDL.h>
#include <iostream>

#include "SDLWindow.h"

SDLWindow::SDLWindow(char* window_title, const unsigned & window_width, const unsigned & window_height)
{
	window_ = SDL_CreateWindow(	window_title,
								SDL_WINDOWPOS_UNDEFINED,
								SDL_WINDOWPOS_UNDEFINED,
								window_width,
								window_height,
								SDL_WINDOW_SHOWN );
	if(window_ == NULL)
	{
		std::cout << "Window could not be created! SDL Error: %s\n" << SDL_GetError();
	}
	else
	{
		renderer_ = SDL_CreateRenderer( window_, -1, SDL_RENDERER_ACCELERATED);
		
		if( renderer_ == NULL)
		{
			std::cout << "Renderer could not be created! SDL Error: %s\n" << SDL_GetError();
		}
	}
}

void SDLWindow::update()
{
	SDL_UpdateWindowSurface(window_);
}