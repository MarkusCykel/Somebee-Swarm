#include "Map.h"
#include <map>

void Map::readInput()
{
		player_->readInput();
		
		for( const auto &i : npcs_ )
		{
			i->readInput();
		}
		
		for( const auto &i : projectiles_ )
		{
			i->readInput();
		}
}

void Map::update()
{
		player_->update();
		
		for( const auto &i : npcs_ )
		{
			i->update();
		}
		
		for( const auto &i : projectiles_ )
		{
			i->update();
		}
}

void Map::spawnEntity(const std::string& param, double x, double y)
{
	static std::map<std::string,int> entity;
	entity["PLAYER"] = 1;
	entity["NPC"] = 2;
	entity["SPAWNER"] = 3;
	entity["PROJECTILE"] = 4;
	
		switch (entity[param])
		{
			case 1 :
				delete player_;
				player_ = new Player{x,y};
				break;
			default :
				std::cerr << "Invalid entity\n";
		}
}

Player* Map::getPlayer()
{
	return player_;
}

std::vector<NPC*> Map::getNpcs()
{
	return npcs_;
}

std::vector<Wall*> Map::getWalls()
{
	return walls_;
}

std::vector<Spawner*> Map::getSpawners()
{
	return spawners_;
}