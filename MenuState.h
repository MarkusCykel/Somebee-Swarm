#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <SDL.h>
#include <vector>

#include "classes.h"
#include "Window.h"
#include "Button.h"

class MenuState
{
	public:
		MenuState(Window& window);
		
		bool run(SDL_Event&);
	private:
		void readInput(SDL_Event&);
		void update();
		void render(); 
		
		Window window_;
		std::vector<Button*> buttons_;
		
		bool quit_;
};


#endif