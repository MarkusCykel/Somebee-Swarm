#include "Entity.h"
#include <iostream>
#include <iomanip>

#define PI 3.14159265

//////////////////////////////
//	Entity
//////////////////////////////

double Entity::getX()
{
	return posX_;
}

double Entity::getY()
{
	return posY_;
}

//////////////////////////////
//	Wall
//////////////////////////////

void Wall::render(SDL_Renderer* renderer, const SDL_Rect & camera)
{
	//Render red filled quad
	SDL_Rect fillRect = { posX_ - int(camera.x + height_/2), posY_ - int(camera.y + width_/2) , height_, width_};
	SDL_SetRenderDrawColor( renderer, 0x5F, 0x5F, 0x5F, 0xFF );
	SDL_RenderFillRect( renderer, &fillRect );
}

