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

void Live_Object::setPosition(double x, double y)
{
	posX_ = x;
	posY_ = y;
}

double Live_Object::getTargetX()
{
	return targetPosX_;
}

double Live_Object::getTargetY()
{
	return targetPosY_;
}

bool Live_Object::getAlive()
{
	return alive_;
}

void Live_Object::setAlive(bool param)
{
	alive_ = param;
}

void Live_Object::checkCollision(Map& map)
{
	double leftA, leftB;
	double rightA, rightB;
	double bottomA, bottomB;
	double topA, topB;
	
	auto Npcs = map.getNpcs();
	
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

			if((bottomA >= topB && topB >= topA || bottomB >= topA && topA >= topB) && (rightA >= leftB && rightB >= leftA || leftA <= rightB && rightA >= rightB))
				std::cout << "COLLISION WOOO" << std::endl;
			else
				std::cout << "nope WOOO" << std::endl;
		}
	 }
}


//////////////////////////////
//	Player
//////////////////////////////


/* Read input and change parameters depending on it */
void Player::readInput()
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
	
	if( currentKeyStates[ SDL_SCANCODE_W ] ^ currentKeyStates[ SDL_SCANCODE_S ]) // If exactly one of W and S is held down
	{
		if(currentKeyStates[ SDL_SCANCODE_S ]) // If it was S, increase speed on x-axis
			if(speedY_ < maxSpeed_)
			{
				speedY_ += acceleration_;
				if(speedY_ > maxSpeed_)	// If speed is greater than max, set it to max
					speedY_ = maxSpeed_;
			}
			
		if(currentKeyStates[ SDL_SCANCODE_W ])	// If it was W decrease speed on x-axis
			if(speedY_ > -maxSpeed_)
			{
				speedY_ -= acceleration_;
				if(speedY_ < -maxSpeed_) // If speed is a bigger negative than the negative max, set it to negative max
					speedY_ = -maxSpeed_;
			}
	}
	else if( speedY_ < 0 ) // If W nor S is held down, deaccelerate
		speedY_ += acceleration_;
	else if( speedY_ > 0 )
		speedY_ -= acceleration_;
		
	
	if( currentKeyStates[ SDL_SCANCODE_A ] ^ currentKeyStates[ SDL_SCANCODE_D ]) // Equivalent to W/S but Y axis instead
	{
		if(currentKeyStates[ SDL_SCANCODE_D ])
			if(speedX_ < maxSpeed_)
			{
				speedX_ += acceleration_;
				if(speedX_ > maxSpeed_)
					speedX_ = maxSpeed_;
			}
			
		if(currentKeyStates[ SDL_SCANCODE_A ])
			if(speedX_ > -maxSpeed_)
			{
				speedX_ -= acceleration_;
				if(speedX_ < -maxSpeed_)
					speedX_ = -maxSpeed_;
			}
	}
	else if( speedX_ < 0 )
		speedX_ += acceleration_;
	else if( speedX_ > 0 )
		speedX_ -= acceleration_;
}


/* Update position depending on speed */
void Player::update()
{
	targetPosX_ = posX_ + speedX_;
	targetPosY_ = posY_ + speedY_;
}

void Player::render(SDL_Renderer* renderer, const SDL_Rect & camera)
{
	//Clear screen

	//Render red filled quad
	SDL_Rect fillRect = { posX_ - int(camera.x + height_/2), posY_ - int(camera.y + width_/2) , height_, width_};
	SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0x00, 0xFF );
	SDL_RenderFillRect( renderer, &fillRect );
}

/* Declares what happens when Player collides with another Entity */
void Player::collision(Entity* param)
{
	//do stuff
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
	//Clear screen

	//Render red filled quad
	SDL_Rect fillRect = { posX_ - int(camera.x + height_/2), posY_ - int(camera.y + width_/2) , height_, width_};
	SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );
	SDL_RenderFillRect( renderer, &fillRect );
}

void NPC::collision(Entity* param)
{
	//do stuff
}


/* It shouldn't have any input? */
void Projectile::readInput()
{
	//do stuff
}

/* Update position depending on speed and  */
void Projectile::update()
{
	targetPosX_ = posX_ + cos(angle_*PI/180)*maxSpeed_;
	targetPosY_ = posY_ + sin(angle_*PI/180)*maxSpeed_;
}

void Projectile::render(SDL_Renderer* renderer, const SDL_Rect & camera)
{
	//Clear screen

	//Render red filled quad
	SDL_Rect fillRect = { posX_ - int(camera.x + height_/2), posY_ - int(camera.y + width_/2) , height_, width_};
	SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0xFF, 0xFF );
	SDL_RenderFillRect( renderer, &fillRect );
}

/* Determines what happens to Projectile when it collides with another Entity */
void Projectile::collision(Entity* param)
{
	//do stuff
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

void Wall::collision(Entity* param)
{
	//do stuff
}


//////////////////////////////
//	Spawner
//////////////////////////////

void Spawner::update()
{
	if(timer_.getTicks() > 10000)
	{
		map_->spawnEntity("NPC", posX_, posY_, width_, height_, maxSpeed_, acceleration_);
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

void Spawner::collision(Entity* param)
{
	//do stuff
}