#ifndef SDLSURFACE_H
#define SDLSURFACE_H

#include <SDL.h>
#include <iostream>

class SDLSurface
{
	public:
		SDLSurface() = default;
		SDLSurface(SDL_Surface* surface) : surface_{surface} {};
		~SDLSurface() = default;
		
		SDLSurface operator=(SDL_Surface* other) { surface_ = other; };
		
		void fill(const unsigned &,const unsigned &,const unsigned &);
		void blitSurface(const SDLSurface& surface);
		void blitSurface(const SDLSurface& surface,const unsigned &,const unsigned &);
		SDL_PixelFormat* get_format() { return surface_->format; };
		bool loadBMP(const std::string&, const SDL_PixelFormat*);
		void stretch(const unsigned &,const unsigned &);
	private:
		SDL_Surface* surface_;
};

#endif