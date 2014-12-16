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
		//Button(const SDL_Rect &, const Uint8 &, const Uint8 &, const Uint8 &, const Uint8 &, const bool & );
		void render(SDL_Renderer*);
		void setbuttonpressed(const bool &);
		void setxywh(int, int, int, int);
		bool buttonpressed(){return buttonpressed_;};
		int getx(){return button_.x;};
		int gety(){return button_.y;};
		int getw(){return button_.w;};
		int geth(){return button_.h;};
		//void setname(std::string str){name = str;};
		//std::string getname(){return name;};
		void setcolor(const Uint8 &, const Uint8 &, const Uint8 &, const Uint8 & );
	private:
		bool buttonpressed_; // If button is pressed
		//std::string name;
		SDL_Rect button_;
		Uint8 R_,G_,B_,A_; // Color and alpha
};

#endif