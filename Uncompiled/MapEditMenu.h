#ifndef MAPEDITMENU_H
#define MAPEDITMENU_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <vector>
#include <iostream>
#include "MapEditclasses.h"
#include "MapEditButton.h"

class MapEditMenu
{
	public:
		MapEditMenu();
		void check_input(int, int, const SDL_Rect &);
		void render(SDL_Renderer* renderer, const SDL_Rect &);
		MapEditButton & get_button(){return buttons_.at(currentpressed);}; 
	private:
		int currentpressed;
		std::vector<MapEditButton>buttons_;
};

#endif