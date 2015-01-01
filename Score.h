#ifndef SCORE_H
#define SCORE_H

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

class Score
{
	public:
		Score(Window& window);
		~Score();
		
		void loadscores(const std::string & path);
		void render();
		
		BUTTON_CODE run(SDL_Event&);
		
	private:
		bool readInput(SDL_Event&);
		std::multimap<unsigned, std::string> scores_;
		std::vector<Button*> buttons_;
		Texture text_;
		Window window_;
		BUTTON_CODE selection_{};
};


#endif