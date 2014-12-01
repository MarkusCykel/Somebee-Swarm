#ifndef MAP_H
#define MAP_H

#include "Entity.h"
#include <vector>

class Map
{
	public:
	
		void update();
		void spawnEntity();
		Player* getPlayer();
		std::vector<NPC*> getNpcs();
		std::vector<Wall*> getWalls();
		std::vector<Spawner*> getSpawners();
		
	private:
		Player* playerEntity_;
		std::vector<NPC*> npcs_;
		std::vector<Wall*> walls_;
		std::vector<Spawner*> spawners_;
		
		unsigned width_;
		unsigned height_;
};

#endif