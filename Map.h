#ifndef MAP_H
#define MAP_H

#include "Entity.h"
#include <vector>

class Map
{
	public:
		void update() = delete;
		void spawnEntity() = delete;
		Player* getPlayer() = delete;
		std::vector<NPC*> getNpcs() = delete;
		std::vector<Wall*> getWalls() = delete;
		std::vector<Spawner*> getSpawners() = delete;
		unsigned getScore() = delete;
		
	private:
		Player* playerEntity_;
		std::vector<NPC*> npcs_;
		std::vector<Wall*> walls_;
		std::vector<Spawner*> spawners_;
};

#endif