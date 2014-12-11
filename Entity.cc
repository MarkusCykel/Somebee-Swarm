#include "Entity.h"
#include "Controller.h"
#include <iostream>
#include <iomanip>

#define PI 3.14159265

//////////////////////////////
//	Entity
//////////////////////////////

double Entity::getX()
{
	return posX_;
}

double Entity::getY()
{
	return posY_;
}


//////////////////////////////
//	Live Object
//////////////////////////////

void LiveObject::setPosition(double x, double y)
{
	posX_ = x;
	posY_ = y;
}

double LiveObject::getTargetX()
{
	return targetPosX_;
}

double LiveObject::getTargetY()
{
	return targetPosY_;
}


bool LiveObject::getAlive()
{
	return alive_;
}

void LiveObject::setAlive(bool alive)
{
	alive_ = alive;
}


/*void LiveObject::checkCollision(Map& map, int& x)
{
	double leftA, leftB;
	double rightA, rightB;
	double bottomA, bottomB;
	double topA, topB;
	
	auto Npcs = map.getNpcs();
	auto Walls = map.getWalls();
	leftA = - (double)width_/2 + posX_;
	rightA = (double)width_/2 + posX_;
	topA = - (double)height_/2 + posY_;
	bottomA = (double)height_/2 + posY_;

	for(auto i: Npcs)
	{
		if(i != this)
		{


			leftB =  - i -> getWidth()/2 + i-> getX();
			rightB = i -> getWidth()/2 + i-> getX();
			topB = - i -> getHeight()/2 + i-> getY();
			bottomB =  i ->getHeight()/2 + i-> getY();

			for(auto j: Walls)
	  		{
	 	
	 	
	 			double leftC =  - j -> getWidth()/2 + j-> getX();
				double rightC = j -> getWidth()/2 + j-> getX();
				double topC = - j -> getHeight()/2 + j-> getY();
				double bottomC =  j ->getHeight()/2 + j-> getY();

				if(topB <= bottomC || bottomB >= topC)
				{
					i -> speedY_=0;
				}
				if(rightB >= leftC || leftB <= rightC)
				{
					i -> speedX_=0;	
			 	}
			}
			if((bottomA >= topB && topB >= topA || bottomB >= topA && topA >= topB) && (rightA >= leftB && rightB >= leftA || leftA <= rightB && rightA >= rightB))
				{
				if (x==1)
					alive_ = false;
				if (x==2)
				{
					std::cout << "debug" << std::endl;
					alive_ = false;
					i -> setAlive(false);
				}
			}
		}
	 }
	
	 for(auto i: Walls)
	 {
	 	
	 	
	 	leftB =  - i -> getWidth()/2 + i-> getX();
		rightB = i -> getWidth()/2 + i-> getX();
		topB = - i -> getHeight()/2 + i-> getY();
		bottomB =  i ->getHeight()/2 + i-> getY();

		if(topA <= bottomB || bottomA >= topB)
		{
			speedY_=0;
		}
		if(rightA >= leftB || leftA <= rightB)
		{
			speedX_=0;	
	 	}
	 } 
}*/


//////////////////////////////
//	Player
//////////////////////////////

/* Read input and change parameters depending on it */
void Player::readInput()
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
	
	if( currentKeyStates[ SDL_SCANCODE_W ] ^ currentKeyStates[ SDL_SCANCODE_S ] )
	{
		if(currentKeyStates[ SDL_SCANCODE_W ]) // If it was S, increase speed on x-axis
			if(speedY_ > -maxSpeed_)
				speedY_ -= acceleration_;
			else
				speedY_ = -maxSpeed_;
		else if(currentKeyStates[ SDL_SCANCODE_S ])
			if(speedY_ < maxSpeed_)
				speedY_ += acceleration_;
			else
				speedY_ = maxSpeed_;
	}
	else if( speedY_ < 0 ) // If W nor S is held down, deaccelerate
		speedY_ += acceleration_;
	else if( speedY_ > 0 )
		speedY_ -= acceleration_;
	
	if( currentKeyStates[ SDL_SCANCODE_A ] ^ currentKeyStates[ SDL_SCANCODE_D ] )
	{
		if( currentKeyStates[ SDL_SCANCODE_A ] ) // If it was S, increase speed on x-axis
			if(speedX_ > -maxSpeed_)
				speedX_ -= acceleration_;
			else
				speedX_ = -maxSpeed_;
		else if( currentKeyStates[ SDL_SCANCODE_D ] )
			if(speedX_ < maxSpeed_)
				speedX_ += acceleration_;
			else
				speedX_ = maxSpeed_;
	}
	else if( speedX_ < 0 )
		speedX_ += acceleration_;
	else if( speedX_ > 0 )
		speedX_ -= acceleration_;
	
	
	std::pair<double,double> move_vector{ std::make_pair(speedX_, speedY_) };
	
	double vector_length = sqrt(pow(move_vector.first,2) + pow(move_vector.second, 2));
	
	if(vector_length != 0)
	{
		move_vector_.first = move_vector.first/vector_length;
		move_vector_.second = move_vector.second/vector_length;
	}
}


/* Update position depending on speed */
void Player::update()
{
	/*targetPosX_ = posX_ + speedX_;
	targetPosY_ = posY_ + speedY_;*/
	if(abs(speedX_) > abs(speedY_))
	{
		targetPosX_ = posX_ + move_vector_.first * abs(speedX_);
		targetPosY_ = posY_ + move_vector_.second * abs(speedX_);
	}
	else
	{
		targetPosX_ = posX_ + move_vector_.first * abs(speedY_);
		targetPosY_ = posY_ + move_vector_.second * abs(speedY_);
	}
}

void Player::render(SDL_Renderer* renderer, const SDL_Rect & camera)
{
	//Render red filled quad
	SDL_Rect fillRect = { posX_ - int(camera.x + height_/2), posY_ - int(camera.y + width_/2) , height_, width_};
	SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0x00, 0xFF );
	SDL_RenderFillRect( renderer, &fillRect );
}

void Player::fire(Map& map, double targetX, double targetY)
{
	std::pair<double,double> move_vector{ std::make_pair(targetX - posX_, targetY - posY_) };
	
	double vector_length = sqrt(pow(move_vector.first,2) + pow(move_vector.second, 2));
	
	if(vector_length != 0)
	{
		move_vector.first = move_vector.first/vector_length;
		move_vector.second = move_vector.second/vector_length;
		
		if(timer_.getTicks() > 100)
		{
			timer_.stop();
		}
			
		if(!timer_.isStarted())
		{
			map.makeProjectile(posX_, posY_, 5, 5, 20, 20, move_vector);
			timer_.start();
		}
	}
}

/* Declares what happens when Player collides with another Entity */
void Player::checkCollision(Map& map)
{
	double leftA, leftB;
	double rightA, rightB;
	double bottomA, bottomB;
	double topA, topB;
	
	auto Npcs = map.getNpcs();
	auto Walls = map.getWalls();

	leftA = - (double)width_/2 + posX_;
	rightA = (double)width_/2 + posX_;
	topA = - (double)height_/2 + posY_;
	bottomA = (double)height_/2 + posY_;

	for(auto i: Npcs)
	{
		leftB =  - i -> getWidth()/2 + i-> getX();
		rightB = i -> getWidth()/2 + i-> getX();
		topB = - i -> getHeight()/2 + i-> getY();
		bottomB =  i ->getHeight()/2 + i-> getY();

		if((bottomA >= topB && topB >= topA || bottomB >= topA && topA >= topB) && (rightA >= leftB && rightB >= leftA || leftA <= rightB && rightA >= rightB))
		{
			alive_ = false;
		}
	}
	
	for(auto i: Walls)
	{
		
		leftB =  - i -> getWidth()/2 + i-> getX();
		rightB = i -> getWidth()/2 + i-> getX();
		topB = - i -> getHeight()/2 + i-> getY();
		bottomB =  i ->getHeight()/2 + i-> getY();

		/*if(topA <= bottomB || bottomA >= topB)
		{
			speedY_=0;
		}*/
		if((bottomA >= topB && topB >= topA || bottomB >= topA && topA >= topB) && (rightA >= leftB && rightB >= leftA || leftA <= rightB && rightA >= rightB))
		{
			speedX_=0;	
	 	}
	} 		
}

//////////////////////////////
//	NPC
//////////////////////////////

void NPC::readInput()
{
	auto player = map_->getPlayer();
	
	auto targetY = player->getY();
	auto targetX = player->getX();
	
	std::pair<double,double> move_vector{ std::make_pair(targetX - posX_, targetY - posY_) };
	
	double vector_length = sqrt(pow(move_vector.first,2) + pow(move_vector.second, 2));
	
	if(vector_length != 0)
	{
		move_vector.first = move_vector.first/vector_length;
		move_vector.second = move_vector.second/vector_length;
		
		if(abs(targetX - posX_) <= abs(move_vector.first * maxSpeed_) && abs(targetY - posY_) <= abs(move_vector.second * maxSpeed_))
		{
			targetPosX_ = targetX;
			targetPosY_ = targetY;
		}
		else
		{
			targetPosX_ = posX_ + move_vector.first * maxSpeed_;
			targetPosY_ = posY_ + move_vector.second * maxSpeed_;
		}
		
	}
}

void NPC::update()
{
	//do stuff
}


void NPC::render(SDL_Renderer* renderer, const SDL_Rect & camera)
{
	//Render red filled quad
	SDL_Rect fillRect = { posX_ - int(camera.x + height_/2), posY_ - int(camera.y + width_/2) , height_, width_};
	SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );
	SDL_RenderFillRect( renderer, &fillRect );
}


void NPC::checkCollision(Map& map)
{
 //bara walls
	double leftA, leftB;
	double rightA, rightB;
	double bottomA, bottomB;
	double topA, topB;
	
	auto Walls = map.getWalls();

	leftA = - (double)width_/2 + targetPosX_;
	rightA = (double)width_/2 + targetPosX_;
	topA = - (double)height_/2 + targetPosY_;
	bottomA = (double)height_/2 + targetPosY_;


	 for(auto i: Walls)
	 {
	 	
	 	leftB =  - i -> getWidth()/2 + i-> getX();
		rightB = i -> getWidth()/2 + i-> getX();
		topB = - i -> getHeight()/2 + i-> getY();
		bottomB =  i ->getHeight()/2 + i-> getY();

		if(topA <= bottomB || bottomA >= topB)
		{
			speedY_=0;
		}
		if(rightA >= leftB || leftA <= rightB)
		{
			speedX_=0;
	 	}
	 } 

}

/* It shouldn't have any input? */
void Projectile::readInput()
{
	//targetPosX_ = posX_ + cos(angle_*PI/180)*maxSpeed_;
	//targetPosY_ = posY_ + sin(angle_*PI/180)*maxSpeed_;
}

/* Update position depending on speed and  */
void Projectile::update()
{
	targetPosX_ = posX_ + move_vector_.first * maxSpeed_;
	targetPosY_ = posY_ + move_vector_.second * maxSpeed_;
}

void Projectile::render(SDL_Renderer* renderer, const SDL_Rect & camera)
{
	//Render red filled quad
	SDL_Rect fillRect = { posX_ - int(camera.x + height_/2), posY_ - int(camera.y + width_/2) , height_, width_};
	SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0xFF, 0xFF );
	SDL_RenderFillRect( renderer, &fillRect );
}

/* Determines what happens to Projectile when it collides with another Entity */
void Projectile::checkCollision(Map& map)
{
	double leftA, leftB;
	double rightA, rightB;
	double bottomA, bottomB;
	double topA, topB;
	
	auto Npcs = map.getNpcs();
	auto Walls = map.getWalls();

	leftA = - (double)width_/2 + posX_;
	rightA = (double)width_/2 + posX_;
	topA = - (double)height_/2 + posY_;
	bottomA = (double)height_/2 + posY_;

	for(auto i: Npcs)
	{
		
		leftB =  - i -> getWidth()/2 + i-> getX();
		rightB = i -> getWidth()/2 + i-> getX();
		topB = - i -> getHeight()/2 + i-> getY();
		bottomB =  i ->getHeight()/2 + i-> getY();

		if((bottomA >= topB && topB >= topA || bottomB >= topA && topA >= topB) && (rightA >= leftB && rightB >= leftA || leftA <= rightB && rightA >= rightB))
		{
			alive_ = false;
			i -> setAlive(false);
		}
	
	}
	for(auto i: Walls)
	{
		
		leftB =  - i -> getWidth()/2 + i-> getX();
		rightB = i -> getWidth()/2 + i-> getX();
		topB = - i -> getHeight()/2 + i-> getY();
		bottomB =  i ->getHeight()/2 + i-> getY();

		if(topA <= bottomB || bottomA >= topB)
		{
			speedY_=0;
		}
		if(rightA >= leftB || leftA <= rightB)
		{
			speedX_=0;
	 	}
	 } 

}

//////////////////////////////
//	Wall
//////////////////////////////

/* Nothing? */
void Wall::update()
{
	//do stuff
}

void Wall::render(SDL_Renderer* renderer, const SDL_Rect & camera)
{
	//Render red filled quad
	SDL_Rect fillRect = { posX_ - int(camera.x + height_/2), posY_ - int(camera.y + width_/2) , height_, width_};
	SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );
	SDL_RenderFillRect( renderer, &fillRect );
}


//////////////////////////////
//	Spawner
//////////////////////////////

void Spawner::update()
{
	if(timer_.getTicks() > 1000)
	{
		map_->makeNPC(posX_, posY_, width_, height_, maxSpeed_, acceleration_);
		timer_.start();
	}
	//do stuff
}

void Spawner::render(SDL_Renderer* renderer, const SDL_Rect & camera)
{
	//Clear screen

	//Render red filled quad
	SDL_Rect fillRect = { posX_ - int(camera.x + height_/2), posY_ - int(camera.y + width_/2) , height_, width_};
	SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );
	SDL_RenderFillRect( renderer, &fillRect );
}