#include <iostream>
#include "SDLWindow.h"
#include "SDLSurface.h"

int main(int argc, char* argv[])
{
	if(SDL_Init(SDL_INIT_VIDEO)<0)
	{
		std::cerr << "sumtingwong";
	}
	else
	{
		SDLWindow window{"lol", 500, 500};	
		if(window.get() == NULL)
		{
			std::cerr << "Window could not be created! SDL_Error: \n" << SDL_GetError();
		}
		else
		{
			bool quit{false};
			SDLSurface surface{window};
			int test{0};
			SDL_Event e;
			while(!quit)
			{		
				while(SDL_PollEvent(&e) != 0)
				{
					if(e.type==SDL_QUIT)
					{
						quit = true;
					}
				}
				
				if(test<255)
					++test;
				else
					test=0;
				surface.fill(test);
				window.update();
				
				SDL_Delay(10);
			}
		}
	}
}