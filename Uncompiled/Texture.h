#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Texture
{
	public:
		Texture();
		~Texture();
		
		void free();
		
		bool loadFromFile( SDL_Renderer*, std::string path  );
		
		bool loadFromFileStretched(  SDL_Renderer*, std::string path, unsigned width, unsigned height);
		
		bool loadFromRenderedText( std::string text, SDL_Color textColor, TTF_Font* font, SDL_Renderer*);
		
		
		void setColor( Uint8 red, Uint8 green, Uint8 blue );
		void setBlendMode( SDL_BlendMode blending );
		void setAlpha( Uint8 alpha);
		
		void render( SDL_Renderer* renderer, SDL_Rect* srcrect, SDL_Rect* dstrect, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
		
		int getWidth() { return width_; }
		int getHeight() { return height_; }
		
	private:
		SDL_Texture* texture_{};
		
		int width_;
		int height_;
};

#endif