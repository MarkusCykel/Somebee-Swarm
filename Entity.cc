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

void LiveObject::setAlive(bool param)
{
	alive_ = param;
}


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

/* Declares what happens when Player collides with another Entity */
void Player::collision(Entity* param)
{
	//do stuff
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
		/*if(abs(targetX - posX_) <= abs(move_vector.first * maxSpeed_) && abs(targetY - posY_) <= abs(move_vector.second * maxSpeed_))
		{
			targetPosX_ = targetX;
			targetPosY_ = targetY;
		}
		else
		{
			targetPosX_ = posX_ + move_vector.first * maxSpeed_;
			targetPosY_ = posY_ + move_vector.second * maxSpeed_;
		}*/
		
	}
	
	//Projectile(int posX, int posY, unsigned width, unsigned height, double maxSpeed, double acceleration, unsigned angle)
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

void Spawner::collision(Entity* param)
{
	//do stuff
}