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
		throw;
	}
	else
	{
		surface_ = SDL_GetWindowSurface(window_);
	}
}

void SDLWindow::update()
{
	SDL_UpdateWindowSurface(window_);
}

void SDLWindow::fill(const unsigned & r,const unsigned & g,const unsigned & b)
{
	surface_.fill(r,g,b);
	update();
}

void SDLWindow::blitSurface(const SDLSurface& surface)
{
	surface_.blitSurface(surface);
	update();
}

void SDLWindow::blitSurface(const SDLSurface& surface,const unsigned & x,const unsigned & y)
{
	surface_.blitSurface(surface,x,y);
	update();
}