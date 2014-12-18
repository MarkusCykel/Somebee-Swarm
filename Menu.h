#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <SDL.h>
#include <vector>

#include "classes.h"
#include "Window.h"
#include "Button.h"
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 50

class Menu
{
	public:
		Menu(Window& window);
		~Menu();
		BUTTON_CODE run(SDL_Event&);
	private:
		bool readInput(SDL_Event&);
		void render(); 
		
		Window window_;
		std::vector<Button*> buttons_;
		Texture background_;
		
		BUTTON_CODE selection_{ BUTTON_PLAY };
};


#endif