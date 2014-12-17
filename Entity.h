#ifndef ENTITY_H
#define ENTITY_H

#include "classes.h"
#include <utility>
#include <SDL.h>
#include <math.h>
#include "Map.h"
#include "Timer.h"

//////////////////////////////
//	Entity
//////////////////////////////

class Entity
{
	public:
		Entity(int posX, int posY, unsigned width, unsigned height) : posX_{posX}, posY_{posY}, width_{width}, height_{height} {};
	
		virtual void render(SDL_Renderer*, const SDL_Rect& camera) = 0;
		
		
		double getX();
		double getY();
		double getWidth() { return width_; }
		double getHeight() { return height_; }
		
	protected:
		double posX_;
		double posY_;
		unsigned width_;
		unsigned height_;
};

//////////////////////////////
//	Static Objects	
//////////////////////////////

class Wall : public Entity
{
	public:
		Wall(int posX, int posY, unsigned width, unsigned height) : Entity{posX, posY, width, height} {};
		
		void render(SDL_Renderer*, const SDL_Rect& camera);
};

class Spawner : public Entity
{
	public:
		Spawner(int posX, int posY, unsigned width, unsigned height) : Entity{posX, posY, width, height} {};
		
		void render(SDL_Renderer*, const SDL_Rect& camera);
};

#endif