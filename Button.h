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
		Button(const SDL_Rect & button, const Uint8 & R = 0xFF, const Uint8 & G = 0x00, const Uint8 & B = 0x00, const Uint8 & A = 0xFF, const bool & press = false);
		
		void handleEvent(SDL_Event& e);
		
		void render(SDL_Renderer*);
		void setButtonPressed(const bool &);
		void setRect(int x, int y, int width, int height);
		bool buttonPressed(){ return buttonPressed_; };
		
		int getX(){return button_.x;};
		int getY(){return button_.y;};
		int getW(){return button_.w;};
		int getH(){return button_.h;};
		
		void setColor(const Uint8 &, const Uint8 &, const Uint8 &, const Uint8 & );
	private:
	
		bool buttonPressed_; // If button is pressed
		SDL_Rect button_;
		Uint8 R_,G_,B_,A_; // Color and alpha
};

#endif