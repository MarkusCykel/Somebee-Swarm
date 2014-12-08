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
	int j{};
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
		if(j > 1)
		{
			check_collisions(map);				
			i->setPosition(x,y);
		}

		j++;
	}

}



void Controller::check_collisions(Map& map)
{
	 
	auto Npcs = map.getNpcs();
	int Nrofnpcs = Npcs.size();
	/*for (int i = 0 ; i < Nrofnpcs ;  ++i )
		{
			auto NpcA = map.getNpcs().at(i);
			auto NpcB = map.getNpcs().at(i+1);
			double leftA, leftB;
			double rightA, rightB;
			double bottomA, bottomB;
			double topA, topB;

			//A
			leftA = NpcA -> getWidth() - NpcA -> getWidth()/2 + NpcA-> getTargetX();
			rightA = NpcA -> getWidth() + NpcA-> getWidth()/2 + NpcA-> getTargetX();
			topA = NpcA -> getHeight() - NpcA -> getHeight()/2 + NpcA-> getTargetY();
			bottomA = NpcA ->getHeight() + NpcA ->getHeight()/2 + NpcA-> getTargetY();

		for (int j = i+1 ; j < Nrofnpcs; ++j)
		{
			
		
			leftB = NpcB -> getWidth() - NpcB->getWidth()/2 + NpcB-> getTargetX() ;
			rightB = NpcB -> getWidth() + NpcB->getWidth()/2 + NpcB-> getTargetX();
			topB = NpcB -> getHeight() - NpcB->getHeight()/2 + NpcB-> getTargetY();
			bottomB = NpcB ->getHeight() + NpcB->getHeight()/2 + NpcB-> getTargetY();

	
		    if( bottomA <= topB )
		    	{
		    		return false;
		       	}

		    if( topA >= bottomB )
		    	{
		         	return false;
		    	}

		    if( rightA <= leftB )
		    	{
		        	return false;
		        }

		    if( leftA >= rightB )
		    	{
		        	return false;
		    	}
		   	else	
		    	return true;
		    		//nope.avi	
		}
			
*/
		
		auto Npcs_ = map.getNpcs();
		auto Player_ = map.getPlayer();
			double leftA, leftB;
			double rightA, rightB;
			double bottomA, bottomB;
			double topA, topB;
 
			leftA = Player_ -> getWidth() - Player_ -> getWidth()/2 + Player_-> getX();
			rightA = Player_ -> getWidth() + Player_-> getWidth()/2 + Player_-> getX();
			topA = Player_ -> getHeight() - Player_ -> getHeight()/2 + Player_-> getY();
			bottomA = Player_ ->getHeight() + Player_ ->getHeight()/2 + Player_-> getY();

		for(auto i: Npcs_)
		{
			leftB = i -> getWidth() - i -> getWidth()/2 + i-> getX();
			rightB = i -> getWidth() + i -> getWidth()/2 + i-> getX();
			topB = i -> getHeight() - i -> getHeight()/2 + i-> getY();
			bottomB = i ->getHeight() + i ->getHeight()/2 + i-> getY();

			if( bottomA <= topB )
		    	{
		    		
		    		Player_-> setAlive(true);
		       	}

		    if( topA >= bottomB )
		    	{
		    		
		         Player_-> setAlive(true);
		    	}

		    if( rightA <= leftB )
		    	{
		    		
		        	Player_-> setAlive(true);
		        }

		    if( leftA >= rightB )
		    	{
		    		Player_-> setAlive(true);
		        	
		    	}
		   	else	
		   		Player_-> setAlive(false);
		   
		   }
}			
