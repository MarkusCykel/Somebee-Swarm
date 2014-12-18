#ifndef MAPEDITENTITY_H
#define MAPEDITENTITY_H

#include "MapEditclasses.h"
#include <utility>
#include <SDL.h>
#include <math.h>
#include "MapEditMap.h"
#include "MapEditTimer.h"

//////////////////////////////
//	MapEditEntity
//////////////////////////////

class MapEditEntity
{
	public:
		MapEditEntity(int posX, int posY, unsigned width, unsigned height) : posX_{posX}, posY_{posY}, width_{width}, height_{height} {};
	
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

class MapEditWall : public MapEditEntity
{
	public:
		MapEditWall(int posX, int posY, unsigned width, unsigned height) : MapEditEntity{posX, posY, width, height} {};
		
		void render(SDL_Renderer*, const SDL_Rect& camera);
};

class MapEditSpawner : public MapEditEntity
{
	public:
		MapEditSpawner(int posX, int posY, unsigned width, unsigned height) : MapEditEntity{posX, posY, width, height} {};
		
		void render(SDL_Renderer*, const SDL_Rect& camera);
};

class MapEditPlayerSpawner : public MapEditEntity
{
	public:
		MapEditPlayerSpawner(int posX, int posY, unsigned width, unsigned height) : MapEditEntity{posX, posY, width, height} {};
		
		void render(SDL_Renderer*, const SDL_Rect& camera);
};

#endif