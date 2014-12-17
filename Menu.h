#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <SDL.h>
#include <vector>

#include "classes.h"
#include "Window.h"
#include "Button.h"
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 50

enum SELECTION
{
	GAME,
	MAP_EDITOR,
	SCORE,
	CREDITS,
	QUIT
};

class Menu
{
	public:
		Menu(Window& window);
		~Menu();
		SELECTION run(SDL_Event&);
	private:
		void readInput(SDL_Event&);
		void update();
		void render(); 
		
		Window window_;
		std::vector<Button*> buttons_;
		Texture background_;
		
		SELECTION selection_{GAME};
		bool selected_{false};
};


#endif