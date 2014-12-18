#ifndef GAME_H
#define GAME_H

#include <vector>

#include "classes.h"
#include "Window.h"
#include "Menu.h"
#include "Play.h"
#include "Submit.h"

#define WINDOW_HEIGHT 1600
#define WINDOW_WIDTH 900


class Game
{
public:
	Game(Window&);
	
	bool run();
	
private:
	Play* play_;
	Menu* menu_;
	Submit* submit_;
	
	SDL_Event e;
	Window window_;

	bool quit_ {false};
};

#endif