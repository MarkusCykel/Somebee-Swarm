#ifndef MAP_H
#define MAP_H

#include "Entity.h"
#include <vector>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

class Map
{
	public:
		Map(unsigned width, unsigned height) 
			: width_{width}, height_{height} {}
		~Map();
			
		double getWidth() const { return width_; }
		double getHeight() const { return height_; }
		
		bool cleanUp(unsigned&);
		void makePlayer(double posX, double posY, unsigned width, unsigned height, double maxSpeed, double acceleration, Uint32 rate_of_fire = 100);
		void makeSpawner(double posX, double posY, unsigned width, unsigned height, double maxSpeed, double acceleration, Uint32 interval = 1000);
		void makeNPC(double posX, double posY, unsigned width, unsigned height, double maxSpeed, double acceleration);
		void makeWall(double posX, double posY, unsigned width, unsigned height);
		void makeProjectile(double posX, double posY, unsigned width, unsigned height, double maxSpeed, double acceleration, std::pair<double,double> move_vector);
		
		void renderBackground(SDL_Renderer*, const SDL_Rect&, const int&, const int&);
		void loadBackground(const std::string&, SDL_Renderer*);
		
		Player* getPlayer();
		std::vector<NPC*>& getNpcs();
		std::vector<Wall*>& getWalls();
		std::vector<Spawner*>& getSpawners();
		std::vector<Projectile*>& getProjectiles();
		
	private:
		Player* player_{};
		std::vector<NPC*> npcs_{};
		std::vector<Projectile*> projectiles_{};
		std::vector<Wall*> walls_{};
		std::vector<Spawner*> spawners_{};
		SDL_Texture* background_{};
		

		double width_;
		double height_;
};

#endif