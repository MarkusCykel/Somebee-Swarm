#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL.h>

#include "classes.h"
#include "Window.h"
#include "Map.h"
#include "Controller.h"
#include "Timer.h"
#include "Entity.h"

class GameState
{
	public:
		GameState(unsigned height, unsigned width, Window& window);
		void run();
		void pause() = delete;
	private:
		void readInput();
		void update();
		void render();
		
		Controller controller_;
		Map map_;
		SDL_Rect camera_;
		Window window_;
		
		Timer capTimer_;
		SDL_Event e;
		
		unsigned score_;
		bool quit_;
};


#endif