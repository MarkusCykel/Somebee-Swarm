#include <SDL.h>
#include <iostream>
#include "SDLWindow.h"
#include "SDLSurface.h"

int main(int argc, char* argv[])
{
	if(SDL_Init(SDL_INIT_VIDEO)<0)
	{
		std::cerr << "Initialization of SDL failed.";
	}
	else
	{
		SDLWindow window{"testing", 500, 500};
		bool quit{false};
		int test{0};
		SDL_Event e;
		
		SDLSurface picture;
		if(picture.loadBMP("../Somebee-Swarm/instruction.bmp", window.get_format()))
		{
			std::cout << "Error loading media";
		}
		else
		{
			window.blitSurface(picture,500,500);
		}
		
		int rgb{0};
		while(!quit)
		{		
			while(SDL_PollEvent(&e) != 0)
			{
				if(e.type == SDL_QUIT)
				{
					quit = true;
				}
				else if (e.type == SDL_KEYUP)
				{
					switch(e.key.keysym.sym)
					{
						case SDLK_w:
							rgb = 1;
						break;
						
						case SDLK_a:
							rgb = 2;
						break;
						
						case SDLK_s:
							rgb = 3;
						break;
						
						case SDLK_d:
							rgb = 4;
						break;	
					}						
					test = 0;
				}
			}
			
			if(test<255)
			{
				++test;
					
				switch(rgb)
				{
					case 1:
						window.fill(test,0,0);
					break;
					
					case 2:
						window.fill(0,test,0);
					break;
					
					case 3:
						window.fill(0,0,test);
					break;
					
					case 4:
						window.fill(test,test,0);
					break;
				}
			}
			
			SDL_Delay(2);
		}
	}
}