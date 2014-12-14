#include "Controller.h"
#include <vector>

void Controller::update(Map& map)
{
	checkCollisionss(map);
}


void Controller::checkCollisionss(Map& map)
{
	 
	auto npcs = &map.getNpcs();
	auto player = map.getPlayer();
	auto projectiles = &map.getProjectiles();
	
	player->checkCollisions(map);
	
	/*for(int i{0}; i<projectiles->size(); ++i)
	{
		projectiles->at(i)->checkCollisions(map);
	}*/
	
	/*for(int i{0}; i < npcs->size(); ++i)
	{
		npcs->at(i)->checkCollisions(map);
	}*/
}
