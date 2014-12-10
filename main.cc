#include <SDL.h>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "classes.h"
#include "SDLWindow.h"
#include "Entity.h"
#include "Timer.h"
#include "Map.h"

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS + 1;

int main(int argc, char* argv[])
{	
	if(SDL_Init(SDL_INIT_VIDEO)<0)
	{
		std::cerr << "Initialization of SDL failed.";
	}
	else
	{
		////////////////////////////////////////////////////////
		// The window and a picture
		SDLWindow window{"testing", 640, 480};
		
		//SDLSurface picture;
		//
		////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////
		// Stuff that is needed
		// Quit flag
		bool quit{false};
		
		// Event Handler
		SDL_Event e;
		//
		////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////
		// Stuff I'm testing
		Map map{1280,960};
		SDL_Rect camera = { 0, 0, 640, 480 };
		map.spawnEntity("PLAYER", 250, 250, 10, 10, 5, 5);
		map.spawnEntity("NPC", 130, 200, 10, 10, 5, 5);
		map.spawnEntity("SPAWNER",100, 354, 3, 3, 1, 1);
		map.spawnEntity("SPAWNER",700, 354, 1, 1, 2, 1);
		map.spawnEntity("SPAWNER", 900, 354, 15, 15, 3, 1);
		map.spawnEntity("SPAWNER", 200, 500, 13, 13, 4, 1);
		map.spawnEntity("SPAWNER", 300, 354, 11, 11, 5, 1);
		map.spawnEntity("SPAWNER",1100, 700, 9, 9, 3, 1);
		map.spawnEntity("PROJECTILE", 10, 10, 10, 10, 10, 1, 30);
		
		Controller controller;
		//
		////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////
		// TIMERS AND COUNTERS FOR FPS STUFF
		//The frames per second timer 
		Timer fpsTimer; 
		
		//The frames per second cap timer 
		Timer capTimer;
		
		//Start counting frames per second
		int countedFrames = 0;
		fpsTimer.start();
		//
		////////////////////////////////////////////////////////
		
		while(!quit)
		{
			capTimer.start();
			
			while(SDL_PollEvent(&e) != 0)
			{
				if(e.type == SDL_QUIT)
				{
					quit = true;
				}
			}
		
			
			// other stuff
			//player.readInput();
			//auto pos = player.getPosition();
			map.readInput();
			map.update();
			controller.update(map);
			
			camera.x = (map.getPlayer()->getX()) - 640/ 2;
			camera.y = (map.getPlayer()->getY()) - 480/ 2;
			map.render(window.getRenderer(),camera);

			////////////////////////////////////////////////////////
			// CALCULATING FPS
			float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
			if( avgFPS > 2000000 )
			{
				avgFPS = 0;
			}
			
			//std::cout << std::setw(13) << "Avg (w/cap) " << countedFrames << std::setw(12) << avgFPS << std::endl;

			++countedFrames;	
			//
			////////////////////////////////////////////////////////
			
			////////////////////////////////////////////////////////
			// LIMIT FPS
			int frameTicks = capTimer.getTicks();
			if( frameTicks < SCREEN_TICKS_PER_FRAME )
			{
				SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
			}
			//
			////////////////////////////////////////////////////////
		}
	}
}