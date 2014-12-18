#ifndef MAPEDITBUTTON_H
#define MAPEDITBUTTON_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <cmath>
#include "MapEditclasses.h"
#include "classes.h"
#include "Texture.h"
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 50


class MapEditButton
{
	public:
		MapEditButton();
		MapEditButton(const SDL_Rect & butt, const Uint8 & R = 0xFF, const Uint8 & G = 0x00, const Uint8 & B = 0x00, const Uint8 & A = 0xFF, const bool & press = false, const std::string & str = "Wall");
		MapEditButton(const int & x, const int & y, const int & w, const int & h, const Uint8 & R = 0xFF, const Uint8 & G = 0x00, const Uint8 & B = 0x00, const Uint8 & A = 0xFF, const bool & press = false, const std::string & str = "Wall");
		void render(SDL_Renderer*);
		
		void setbuttonpressed(const bool &);
		void setRect(int x, int y, int width, int height);
		
		bool buttonpressed(){return buttonpressed_;};
		int getx(){return button_.x;};
		int gety(){return button_.y;};
		int getw(){return button_.w;};
		int geth(){return button_.h;};
		void setname(std::string str){name = str;};
		std::string getname(){return name;};
		void setcolor(const Uint8 &, const Uint8 &, const Uint8 &, const Uint8 & );
	private:
		bool buttonpressed_; // If button is pressed
		std::string name;
		Texture text_;
		SDL_Rect button_;
		Uint8 R_,G_,B_,A_; // Color and alpha
};

#endif