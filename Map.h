#ifndef MAP_H
#define MAP_H

#include "Entity.h"
#include <vector>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "classes.h"
#include "CameraController.h"

class Map
{
	public:
		Map(unsigned width, unsigned height) 
			: width_{width}, height_{height} {}
			
		double getWidth();
		double getHeight();
		
		void makeCameraController(double maxSpeed, double acceleration);
		void makeWall(double posX, double posY, unsigned width, unsigned height);
		
		void renderBackground(SDL_Renderer*, const SDL_Rect&, const int&, const int&);
		void loadBackground(const std::string&, SDL_Renderer*);
		
		CameraController* getCameraController();
		std::vector<Wall*>& getWalls();
		
	private:
		CameraController* CameraController_{};
		std::vector<Wall*> walls_{};
		SDL_Texture* background_{};

		double width_;
		double height_;
};

#endif