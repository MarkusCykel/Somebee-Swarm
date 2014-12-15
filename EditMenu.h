#ifndef EDITMENU_H
#define EDITMENU_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "classes.h"

class EditMenu
{
	public:
		EditMenu(): buttonpressed_{false}{};
		void check_input(int, int, const SDL_Rect &);
		void render(SDL_Renderer* renderer, const SDL_Rect &);
		bool buttonpressed(){return buttonpressed_;};
	private:
		bool buttonpressed_;
};

#endif