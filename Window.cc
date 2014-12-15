#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Window.h"

Window::Window(char* window_title, const unsigned & window_width, const unsigned & window_height)
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
		renderer_ = SDL_CreateRenderer( window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		
		if( renderer_ == NULL)
		{
			std::cout << "Renderer could not be created! SDL Error: %s\n" << SDL_GetError();
		}
	}
}

Window::~Window()
{
	//Destroy window	
	SDL_DestroyRenderer( renderer_ );
	SDL_DestroyWindow( window_ );
	
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int Window::getWidth()
{
	return SDL_GetWindowSurface(window_)->w;
}

int Window::getHeight()
{
	return SDL_GetWindowSurface(window_)->h;
}

SDL_Surface* Window::getSurface()
{
	return SDL_GetWindowSurface(window_);
}

void Window::update()
{
	SDL_RenderPresent( renderer_ );
}