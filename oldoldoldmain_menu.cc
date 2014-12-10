//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>

#include "menu.h"

const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 700;

bool init(); //Starts SDL
bool loadLogo(); //Load the game logo
void close(); //Shuts down SDL (not sure if im going to keep this)

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gLogo = NULL;
SDL_Surface* gImage = NULL;

int main (int argc, char* args[])
{
	if (!init())
	{
		printf ("Failed to initialize!\n");
	}else{
		if (!loadLogo())
		{
			printf ("Failed to load logo!\n");
		}else{
			bool quit = false;
			SDL_Event e;
			while (!quit)
			{

				while (SDL_PollEvent (&e) !=0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}
				SDL_BlitSurface (gLogo, NULL, gScreenSurface, NULL);
				SDL_UpdateWindowSurface (gWindow);
			}
		}
	}
	close ();
	return 0;
}

bool init()
{
	bool success = true;
	if (SDL_Init (SDL_INIT_VIDEO) <0)
	{
		printf ("SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}else{
		gWindow = SDL_CreateWindow ("Zombee Swarm", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}else{
			gScreenSurface = SDL_GetWindowSurface (gWindow);
		}
	}
	return success;
}

bool loadLogo()
{
	bool success = true;
	gLogo = IMG_Load ("Menu/Original.jpg");
	if (gLogo == NULL)
	{
		printf("Unable to load image %s! SDL SDL_Error: %s\n", "Menu/Original.jpg", SDL_GetError() );
		success = false;
	}
	gImage = IMG_Load ("Menu/Image.jpg");
	if (gImage == NULL)
	{
		printf("Unable to load image %s! SDL SDL_Error: %s\n", "Menu/Image.jpg", SDL_GetError() );
		success = false;
	}
	return success;
}

void close()
{
	SDL_FreeSurface (gLogo);
	gLogo = NULL;
	SDL_FreeSurface (gImage);
	gImage = NULL;
	SDL_DestroyWindow (gWindow);
	gWindow = NULL;
	SDL_Quit();
}