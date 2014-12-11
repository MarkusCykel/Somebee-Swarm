#include "Controller.h"
#include <vector>

void Controller::update(Map& map)
{
	checkCollisions(map);
}


void Controller::checkCollisions(Map& map)
{
	 
	auto npcs = &map.getNpcs();
	auto player = map.getPlayer();
	auto projectiles = &map.getProjectiles();
	
	player->checkCollision(map);
	
	/*for(int i{0}; i<projectiles->size(); ++i)
	{
		projectiles->at(i)->checkCollision(map);
	}*/
	
	/*for(int i{0}; i < npcs->size(); ++i)
	{
		npcs->at(i)->checkCollision(map);
	}*/
}
