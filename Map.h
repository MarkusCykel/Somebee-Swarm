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
		void readInput();
		void update();
		void render() = delete;
		void spawnEntity(const std::string&, double, double);
		Player* getPlayer();
		std::vector<NPC*> getNpcs();
		std::vector<Wall*> getWalls();
		std::vector<Spawner*> getSpawners();
		
	private:
		Player* player_;
		std::vector<NPC*> npcs_;
		std::vector<Projectile*> projectiles_;
		std::vector<Wall*> walls_;
		std::vector<Spawner*> spawners_;
		
		unsigned width_;
		unsigned height_;
};

#endif