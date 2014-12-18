#ifndef MAPEDITGAMESTATE_H
#define MAPEDITGAMESTATE_H

#include <SDL.h>

#include "MapEditclasses.h"
#include "MapEditWindow.h"
#include "MapEditMap.h"
#include "MapEditTimer.h"
#include "MapEditEntity.h"
#include "MapEditCameraController.h"
#include "MapEditMenu.h"

class MapEditGameState
{
	public:
		MapEditGameState(unsigned height, unsigned width, MapEditWindow& window);
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
		MapEditWindow window_;
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