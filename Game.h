#ifndef GAME_H
#define GAME_H

#include <vector>

#include "classes.h"
#include "Window.h"
#include "Menu.h"
#include "Play.h"
#include "Submit.h"
#include "Edit.h"

#define WINDOW_HEIGHT 1600
#define WINDOW_WIDTH 900


class Game
{
public:
	Game(Window&);
	
	bool run();
	
private:
	Menu* menu_;
	Edit* edit_;
	Submit* submit_;
	Play* play_;
	
	SDL_Event e;
	Window window_;

	bool quit_ {false};
};

#endif