#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL.h>

#include "classes.h"
#include "Window.h"
#include "Map.h"
#include "Timer.h"
#include "Entity.h"

class MenuState
{
	public:
		MenuState(unsigned height, unsigned width, Window& window);
		
		void run(SDL_Event&);
	private:
		void readInput(SDL_Event&);
		void update();
		void render(); 
		
		Window window_;
		
		bool quit_;
};


#endif