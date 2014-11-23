#include "SDLWindow.h"

SDLWindow::SDLWindow(char* window_title, const int window_width, const int window_height)
{
	window_ = SDL_CreateWindow(window_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_SHOWN );
}

void SDLWindow::update()
{
	SDL_UpdateWindowSurface( window_ );
}