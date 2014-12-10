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
		
		check_collisions(map);
		i->setPosition(x,y);
	}

}



void Controller::check_collisions(Map& map)
{
	 
	auto Npcs = map.getNpcs();
	auto Player_ = map.getPlayer();
	int Nrofnpcs = Npcs.size();
	int x = 1;
	Player_->checkCollision(map, x);
	auto projectiles = map.getProjectiles();
	for( auto i : projectiles)
		{
			x = 2;
			i->checkCollision(map, x);
		}
	/*double leftA, leftB;
	double rightA, rightB;
	double bottomA, bottomB;
	double topA, topB;
	
	for (int i = 0 ; i < Nrofnpcs-1;  ++i )
	{
			auto NpcA = map.getNpcs().at(i);
			auto NpcB = map.getNpcs().at(i+1);
			

			//A
			leftA = NpcA -> getWidth() - NpcA -> getWidth()/2 + NpcA-> getTargetX();
			rightA = NpcA -> getWidth() + NpcA-> getWidth()/2 + NpcA-> getTargetX();
			topA = NpcA -> getHeight() - NpcA -> getHeight()/2 + NpcA-> getTargetY();
			bottomA = NpcA ->getHeight() + NpcA ->getHeight()/2 + NpcA-> getTargetY();

		for (int j = i+1 ; j < Nrofnpcs-1; ++j)
		{
			
		
			leftB = NpcB -> getWidth() - NpcB->getWidth()/2 + NpcB-> getTargetX() ;
			rightB = NpcB -> getWidth() + NpcB->getWidth()/2 + NpcB-> getTargetX();
			topB = NpcB -> getHeight() - NpcB->getHeight()/2 + NpcB-> getTargetY();
			bottomB = NpcB ->getHeight() + NpcB->getHeight()/2 + NpcB-> getTargetY();

	
		    if( (bottomA > topB && topB > topA || bottomB > topA && topA > topB) && (rightA > leftB && leftB > leftA || leftA > rightB && rightB > leftB))
				std::cout << "COLLISION WOOO" << std::endl;
		}
	}
 
	leftA = - Player_ -> getWidth()/2 + Player_-> getX();
	rightA = Player_-> getWidth()/2 + Player_-> getX();
	topA = - Player_ -> getHeight()/2 + Player_-> getY();
	bottomA = Player_ ->getHeight()/2 + Player_-> getY();

	for(auto i: Npcs)
	{
		leftB =  - i -> getWidth()/2 + i-> getX();
		rightB = i -> getWidth()/2 + i-> getX();
		topB = - i -> getHeight()/2 + i-> getY();
		bottomB =  i ->getHeight()/2 + i-> getY();

		if((bottomA >= topB && topB >= topA || bottomB >= topA && topA >= topB) && (rightA >= leftB && rightB >= leftA || leftA <= rightB && rightA >= rightB))
			std::cout << "COLLISION WOOO" << std::endl;
		else
			std::cout << "nope WOOO" << std::endl;
	   
	 }*/

}			
