#ifndef CREDIT_H
#define CREDIT_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include <iomanip>

#include "classes.h"
#include "Texture.h"
#include "Window.h"
#include "Button.h"

class Credit
{
	public:
		Credit(Window& window);
		~Credit();
		
		void render();
		
		BUTTON_CODE run(SDL_Event&);
		
	private:
		bool readInput(SDL_Event&);
		std::vector<std::string>credits_;
		std::vector<Button*> buttons_;
		Texture text_;
		Window window_;
		BUTTON_CODE selection_{};
};


#endif