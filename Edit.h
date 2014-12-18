#ifndef EDIT_H
#define EDIT_H

#include <SDL.h>

#include "MapEditclasses.h"
#include "Window.h"
#include "MapEditMap.h"
#include "MapEditTimer.h"
#include "MapEditEntity.h"
#include "MapEditCameraController.h"
#include "MapEditMenu.h"

class Edit
{
	public:
		Edit(unsigned height, unsigned width, Window& window);
		void run(SDL_Event&);
	private:
		void pause() = delete;
		void readInput(SDL_Event&);
		void update();
		void render();
		bool collision();
		bool menu();
		bool outofbounds();
		
		MapEditMap map_;
		SDL_Rect camera_;
		Window window_;
		SDL_Rect mapViewport{0, 0, window_.getWidth() * 3/4, window_.getHeight()};
		SDL_Rect menuViewport{window_.getWidth()-window_.getWidth()*1/4, 0, window_.getWidth() * 1/4, window_.getHeight()};
		int mouseposX;
		int mouseposY;
		MapEditTimer capTimer_;
		MapEditMenu menu_;
		
		
		SDL_Rect square{0,0,30,30};
		bool intersectiftrue;
		bool gameOver_;
		bool quit_;
};


#endif