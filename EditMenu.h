#ifndef EDITMENU_H
#define EDITMENU_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <vector>
#include <iostream>
#include "classes.h"
#include "Button.h"

class EditMenu
{
	public:
		EditMenu();
		void check_input(int, int, const SDL_Rect &);
		void render(SDL_Renderer* renderer, const SDL_Rect &);
		Button get_button(){return buttons_.at(currentpressed);}; 
	private:
		int currentpressed;
		std::vector<Button>buttons_;
};

#endif