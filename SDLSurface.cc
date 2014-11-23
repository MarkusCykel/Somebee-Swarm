#include "SDLSurface.h"

SDLSurface::SDLSurface(const SDLWindow & window)
{
	surface_ = SDL_GetWindowSurface(window.get());
}

void SDLSurface::fill(int blue)
{
	SDL_FillRect( surface_, NULL, SDL_MapRGB( surface_->format, 0x00, 0x00, blue ) );
}