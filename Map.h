#ifndef MAP_H
#define MAP_H

#include "Entity.h"
#include "Controller.h"
#include <vector>
#include <iostream>

class Map
{
	public:
		Map(unsigned width, unsigned height) 
			: width_{width}, height_{height} {}
			
		double getWidth();
		double getHeight();
		
		void readInput();
		void update();
		void render(SDL_Renderer*, const SDL_Rect&);
		void spawnEntity(const std::string& param, int posX, int posY, unsigned width, unsigned height, double maxSpeed, double acceleration, unsigned angle = 0, Uint32 interval = 10000);
		Player* getPlayer();
		std::vector<NPC*> getNpcs();
		std::vector<Wall*> getWalls();
		std::vector<Spawner*> getSpawners();
		std::vector<Projectile*> getProjectiles();
		
	private:
		Player* player_{};
		std::vector<NPC*> npcs_{};
		std::vector<Projectile*> projectiles_{};
		std::vector<Wall*> walls_{};
		std::vector<Spawner*> spawners_{};
		
		double width_;
		double height_;
};

#endif