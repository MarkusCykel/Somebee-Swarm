#include "SDLSurface.h"

void SDLSurface::fill(const unsigned & red, const unsigned & green, const unsigned & blue)
{
	SDL_FillRect( surface_, NULL, SDL_MapRGB( surface_->format, red, green, blue ) );
}

void SDLSurface::blitSurface(const SDLSurface& surface)
{
	SDL_BlitSurface(surface.surface_, NULL, surface_, NULL);
}

void SDLSurface::blitSurface(const SDLSurface& surface,const unsigned & x,const unsigned & y)
{
	SDL_Rect stretchRect;
	stretchRect.x = 0;
	stretchRect.y = 0;
	stretchRect.w = x;
	stretchRect.h = y;
	SDL_BlitScaled(surface.surface_, NULL, surface_, &stretchRect);
}

bool SDLSurface::loadBMP(const std::string & media, const SDL_PixelFormat* format)
{	
	SDL_Surface* loadedSurface = SDL_LoadBMP(media.c_str());
	
	if(loadedSurface == NULL)
	{
		return 1;
	}
	else
	{
		surface_ = SDL_ConvertSurface(loadedSurface,format,NULL);
		
		SDL_FreeSurface(loadedSurface);
	}
	
	return 0;
}