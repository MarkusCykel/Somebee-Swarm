#ifndef MAPEDITMAP_H
#define MAPEDITMAP_H

#include "MapEditclasses.h"
#include "MapEditEntity.h"
#include <vector>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "MapEditCameraController.h"
#include <fstream>
#include <sstream>
class MapEditMap
{
	public:
		MapEditMap(unsigned width, unsigned height) 
			: width_{width}, height_{height}, playerspawner_{NULL},CameraController_{NULL} {}
		
		~MapEditMap()
		{
			std::cout<<"HEy"<<std::endl;
			delete CameraController_;
			delete playerspawner_;
	
			for(auto& i : walls_)
			{
				delete i;
			}
			
			for(auto& i : spawners_)
			{
				delete i;
			}
			SDL_DestroyTexture( background_ );
		}
		
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
		
		MapEditCameraController* getCameraController();
		std::vector<MapEditWall*>& getWalls();
		std::vector<MapEditSpawner*>& getSpawners();
		MapEditPlayerSpawner* getPlayerSpawner();
		
	private:
		MapEditCameraController* CameraController_{};
		std::vector<MapEditWall*> walls_{};
		std::vector<MapEditSpawner*> spawners_{};
		MapEditPlayerSpawner* playerspawner_{};
		SDL_Texture* background_{};

		void delete_walls();
		void delete_spawners();
		double width_;
		double height_;
};

#endif