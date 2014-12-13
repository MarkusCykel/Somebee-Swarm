#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL.h>

#include "classes.h"
#include "Window.h"
#include "Map.h"
#include "Timer.h"
#include "Entity.h"
#include "CameraController.h"
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
		bool menu();
		bool outofbounds();
		
		Map map_;
		SDL_Rect camera_;
		Window window_;
		SDL_Rect mapViewport{0, 0, window_.getWidth() * 3/4, window_.getHeight()};
		SDL_Rect menuViewport{window_.getWidth()-window_.getWidth()*1/4, 0, window_.getWidth() * 1/4, window_.getHeight()};
		int mouseposX;
		int mouseposY;
		Timer capTimer_;
		
		bool gameOver_;
		bool quit_;
};


#endif