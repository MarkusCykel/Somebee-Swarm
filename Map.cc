#include "Map.h"

void Map::update()
{
	
}

void Map::spawnEntity()
{
}

Player* Map::getPlayer()
{
	return playerEntity_;
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

unsigned Map::getScore()
{
	return 0;
}