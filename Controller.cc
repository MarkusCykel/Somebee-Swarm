#include "Controller.h"
#include <vector>

void Controller::update(Map& map)
{
	auto player = map.getPlayer();
	
	double x, y;
	
	if( player->getTargetX() > map.getWidth() )
		x = map.getWidth();
	else if( player->getTargetX() < 0 )
		x = 0;
	else
		x = player->getTargetX();
	
	if( player->getTargetY() > map.getHeight() )
		y = map.getHeight();
	else if( player->getTargetY() < 0 )
		y = 0;
	else
		y = player->getTargetY();
		
	player->setPosition(x, y);
	
	auto projectiles = map.getProjectiles();
	
	for(auto i : projectiles)
	{
		if( i->getTargetX() > map.getWidth() )
			x = map.getWidth();
		else if( i->getTargetX() < 0 )
			x = 0;
		else
			x = i->getTargetX();
		
		if( i->getTargetY() > map.getHeight() )
			y = map.getHeight();
		else if( i->getTargetY() < 0 )
			y = 0;
		else
			y = i->getTargetY();
			
		i->setPosition(x,y);
	}
	
	auto npcs = map.getNpcs();
	
	for(auto i : npcs)
	{
		if( i->getTargetX() > map.getWidth() )
			x = map.getWidth();
		else if( i->getTargetX() < 0 )
			x = 0;
		else
			x = i->getTargetX();
		
		if( i->getTargetY() > map.getHeight() )
			y = map.getHeight();
		else if( i->getTargetY() < 0 )
			y = 0;
		else
			y = i->getTargetY();
		
		i->setPosition(x,y);
	}
	
	checkCollisions(map);
}


void Controller::checkCollisions(Map& map)
{
	 
	auto Npcs = &map.getNpcs();
	auto Player = map.getPlayer();
	int Nrofnpcs = Npcs->size();
	Player->checkCollision(map);
	auto projectiles = &map.getProjectiles();
	
	for(int i{0}; i<projectiles->size(); ++i)
	{
		projectiles->at(i)->checkCollision(map);
	}
}
