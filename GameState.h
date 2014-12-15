#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL.h>

#include "classes.h"
#include "Window.h"
#include "Map.h"
#include "Timer.h"
#include "Entity.h"

class GameState
{
	public:
		GameState(unsigned height, unsigned width, Window& window);
		
		void run(SDL_Event&);
	private:
		void pause() = delete;
		void readInput(SDL_Event&);
		void update();
		void render();
		
		Map map_;
		SDL_Rect camera_;
		Window window_;
		
		Timer capTimer_;
		
		unsigned score_;
		bool gameOver_;
		bool quit_;
};


#endif