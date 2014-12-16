#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>

//#include "menu.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

//Button constants
const int BUTTON_WIDTH = 175;
const int BUTTON_HEIGHT = 100;
const int TOTAL_BUTTONS = 4;

enum ButtonSprite
{
    BUTTON_SPRITE_GAME = 0,
    BUTTON_SPRITE_SCORE = 1,
    BUTTON_SPRITE_CREDITS = 2,
    BUTTON_SPRITE_QUIT = 3,
    BUTTON_SPRITE_TOTAL = 4
};

class Texture
{
public:
	Texture ();
	~Texture ();
	bool loadFromFile (std::string path);
	void free ();
	void setColor (Uint8 red, Uint8 green, Uint8 blue);
	void setBlendMode (SDL_BlendMode blending);
	void setAlpha (Uint8 alpha);
	void render (int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	int getWidth ();
	int getHeight ();
private:
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
};

class Button
{
public:
	Button();
	void setPosistion (int x, int y);
	void handleEvent (SDL_Event* e);
	void render ();
private:
	//Top Left position
	SDL_Point mPosition;
	//Currentlu used sprite
	ButtonSprite mCurrentSprite;
};

bool init ();
bool loadMedia ();
void close ();
void Game ();
void High_Score ();
void Credits ();
void Quit ();

SDL_Texture* loadTexture (std::string path);
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;
SDL_Rect gSpriteClips [BUTTON_SPRITE_TOTAL];
Texture gButtonSpiteSheetTexture;
Button gButtons [TOTAL_BUTTONS];

Texture::Texture ()
{
	mTexture = NULL;
	
}

Button::Button ()
{
	mPosition.x = 0;
	mPosition.y = 0;
}

void Button::setPosition (int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;
}

void Button::handleEvent (SDL_Event* e)
{
	//If leftclick event happened
	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		//Get mouse pos
		int x, y;
		SDL_GetMouseState (&x, &y);
		//Check if inside button
		bool inside = true;
		if (x < mPosition.x) //IF left of button
		{
			inside = false;
		}
		else if (x > mPosition.x + BUTTON_WIDTH) //IF right of button
		{
			inside = false;
		}
		else if (y < mPosition.y) //IF above
		{
			inside = false;
		}
		else if (y > mPosition.y + BUTTON_HEIGHT) //IF below
		{
			inside = false;
		}
//=============================================== /I HAVE NO IDEA IF THIS WORKS/
		if (inside)
		{
			switch (e->type)
			{
				case BUTTON_SPRITE_GAME:
				Game ();
				break;

				case BUTTON_SPRITE_SCORE:
				High_Score ();
				break;

				case BUTTON_SPRITE_CREDITS:
				Credits ();
				break;

				case BUTTON_SPRITE_QUIT:
				Quit ();
				break;
			}
		}
//================================================= */I HAVE NO IDEA IF THIS WORKS/
	}
}

void Button::render()
{
	//current sprite
	gButtonSpiteSheetTexture.render (mPosition.x, mPosition.y, &gSpriteClips [mCurrentSprite]);
}

bool init ()
{
	bool success = true;
	if (SDL_Init (SDL_INIT_VIDEO) <0)
	{
		printf("SDL could not init! SDL Error: %s\n", SDL_GetError ());
		success = false;
	}else{
		if (!SDL_SetHint (SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf ("Warning!: Linear texture filtering not enabled!");
		}
		gWindow = SDL_CreateWindow ("Zombee Swarm", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf ("Window could not be created! SDL Error: %s\n", SDL_GetError ());
			success = false;
		}else{
			gRenderer = SDL_CreateRenderer (gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PREVENTVSYNC);
			if (gRenderer == NULL)
			{
				printf ("Renderer could not be created! SDL Error: %s\n", SDL_GetError ());
				success = false;
			}else{
				SDL_SetRenderDrawColor (gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init (imgFlags) & imgFlags))
				{
					printf ("SDL_image could not init! SDL_image Error: %s\n", IMG_GetError ());
					success = false;
				}
			}
		}
	}
	return success;
}

bool loadMedia ()
{
	bool success = true;

	return success;
}

void close ()
{
	//Free loaded images
	gTextTexture.free();
	//Free global font
	TTF_CloseFont( gFont );
	gFont = NULL;
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Game()
{
	
}

void Credits()
{
	
}

void High_Score()
{
	
}

void Quit()
{
	quit = true;
}

int main (int argc, char* args [])
{
	if (!init ())
	{
		printf ("Failed to init!\n");
	}else{
		if (!loadMedia ())
		{
			printf ("Failed to load media!\n");
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
					for (int i = 0; i < TOTAL_BUTTONS; ++i)
					{
						gButtons [i].handleEvent (&e);
					}
				}
				//Clear screen
				SDL_SetRenderDrawColor (gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear (gRenderer);
				//Render buttons
				for (int i = 0; i < TOTAL_BUTTONS; ++i)
				{
					gButtons [i].render ();
				}
				//Update screen
				SDL_RenderPresent (gRenderer);
			}
		}
	}
	close ();
	return 0;
}