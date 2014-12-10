#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>

#include "menu.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

//Button constants
const int BUTTON_WIDTH = 175;
const int BUTTON_HEIGHT = 100;
const int TOTAL_BUTTONS = 4;

enum LButtonSprite
{
    BUTTON_SPRITE_GAME = 0,
    BUTTON_SPRITE_SCORE = 1,
    BUTTON_SPRITE_CREDITS = 2,
    BUTTON_SPRITE_QUIT = 3,
    BUTTON_SPRITE_TOTAL = 4
};

Button::Button()
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

}

