#ifndef BUTTON_H
#define BUTTON_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "classes.h"


class Button
{
	public:
		Button();
		Button(const Uint8 &, const Uint8 &, const Uint8 &, const Uint8 &, const SDL_Rect &, const bool & );
		void render(SDL_Renderer*);
		void setbuttonpressed(const bool &);
		bool buttonpressed(){return buttonpressed_;};
		void setcolor(const Uint8 &, const Uint8 &, const Uint8 &, const Uint8 & );
	private:
		bool buttonpressed_; // If button is pressed
		SDL_Rect button_;
		Uint8 R_,G_,B_,A_; // Color and alpha
};

#endif