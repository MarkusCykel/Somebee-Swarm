#include "Controller.h"

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
	
	auto projectiles_ = map.getProjectiles();
	
	for(auto i : projectiles_)
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
	
	auto npcs_ = map.getNpcs();
	
	for(auto i : npcs_)
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
}


void Controller::check_collisions()
{
	
}