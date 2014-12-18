#ifndef SUBMIT_H
#define SUBMIT_H

#include <SDL.h>
#include <vector>

#include "Window.h"
#include "Button.h"

class Submit
{
	public:
		Submit(Window& window);
		~Submit();
		
		BUTTON_CODE run(SDL_Event&);
		
		std::string getNick() { return nick_; }
	private:
		bool readInput(SDL_Event&);
		void render(); 
		
		Window window_;
		std::vector<Button*> buttons_;
		Texture textTexture_;
		std::string nick_;
		BUTTON_CODE selection_{};
};

#endif