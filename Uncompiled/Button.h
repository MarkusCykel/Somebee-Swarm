#ifndef BUTTON_H
#define BUTTON_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <cmath>
#include "classes.h"
#include "Texture.h"
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 50

enum BUTTON_CODE
{
	// Menu Buttons
	BUTTON_PLAY,
	BUTTON_MAP_EDITOR,
	BUTTON_SCORE,
	BUTTON_CREDITS,
	BUTTON_QUIT,
	
	// General Buttons
	BUTTON_BACK,
	BUTTON_CANCEL,
	BUTTON_SUBMIT
};

class Button
{
	public:
		Button(SDL_Renderer* renderer, std::string text, const SDL_Point & button, BUTTON_CODE id, const Uint8 & R = 0xFF, const Uint8 & G = 0x00, const Uint8 & B = 0x00, const Uint8 & A = 0xFF);
		
		BUTTON_CODE handleEvent(SDL_Event& e);
		
		void render(SDL_Renderer*);
		
		void setPosition(int x, int y);
		
		SDL_Point getPosition() { return position_; };
		
		int getX(){return position_.x;};
		int getY(){return position_.y;};
		
		void setColor(const Uint8 &, const Uint8 &, const Uint8 &, const Uint8 & );
	private:
	
		SDL_Point position_;
		
		BUTTON_CODE id_;
		Texture text_;
		Uint8 R_,G_,B_,A_; // Color and alpha
};

#endif