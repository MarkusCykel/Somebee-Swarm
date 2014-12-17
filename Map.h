#ifndef MAP_H
#define MAP_H

#include "classes.h"
#include "Entity.h"
#include <vector>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "CameraController.h"

class Map
{
	public:
		Map(unsigned width, unsigned height) 
			: width_{width}, height_{height}, playerspawner_{NULL} {}
			
		double getWidth();
		double getHeight();
		
		void makeCameraController(double maxSpeed, double acceleration);
		void makeWall(double posX, double posY, unsigned width, unsigned height);
		void makeSpawner(double posX, double posY, unsigned width, unsigned height);
		void makePlayerSpawner(double posX, double posY, unsigned width, unsigned height);
		
		void renderBackground(SDL_Renderer*, const SDL_Rect&, const int&, const int&);
		void loadBackground(const std::string&, SDL_Renderer*);
		
		void saveMap();
		void loadMap();
		
		CameraController* getCameraController();
		std::vector<Wall*>& getWalls();
		std::vector<Spawner*>& getSpawners();
		PlayerSpawner* getPlayerSpawner();
		
	private:
		CameraController* CameraController_{};
		std::vector<Wall*> walls_{};
		std::vector<Spawner*> spawners_{};
		PlayerSpawner* playerspawner_{};
		SDL_Texture* background_{};

		double width_;
		double height_;
};

#endif