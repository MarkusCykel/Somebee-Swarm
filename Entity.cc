#include "Entity.h"
#include "Controller.h"
#include <math.h>

//////////////////////////////
//	Entity
//////////////////////////////

void Entity::render(SDL_Renderer* renderer)
{	
	//Render red filled quad
	SDL_Rect fillRect = { posY_ - height_/2, posX_-width_/2, width_, height_};
	SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );		
	SDL_RenderFillRect( renderer, &fillRect );
}

double Entity::getX()
{
	return posX_;
}

double Entity::getY()
{
	return posY_;
}

bool Entity::getAlive()
{
	return alive_;
}

void Entity::setAlive(bool param)
{
	alive_ = param;
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

void Player::readInput()
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
	double maxSpeedX_{5}, maxSpeedY_{5};
	int c = 0;

	if (currentKeyStates [SDL_SCANCODE_W] && (currentKeyStates [SDL_SCANCODE_D] ^ currentKeyStates [SDL_SCANCODE_A]))
	{
		c = sqrt(2);
		//c = sqrt(maxSpeedX_ * maxSpeedX_ + maxSpeedY_ * maxSpeedY_);
		maxSpeedX_ = c;
		maxSpeedY_ = c;
		if (currentKeyStates [SDL_SCANCODE_W] && currentKeyStates[SDL_SCANCODE_D])
		{
			if (speedX_ < maxSpeedX_)
			{
				speedX_ += 0.5;
				if (speedX_ > maxSpeedX_)
				{
					speedX_ = maxSpeedX_;
				}
			}
			if (speedY_ < maxSpeedY_)
			{
				speedY_ += 0.5;
				if (speedY_ > maxSpeedY_)
				{
					speedY_ = maxSpeedY_;
				}
			}
		}
		if (currentKeyStates [SDL_SCANCODE_W] && currentKeyStates [SDL_SCANCODE_A])
		{
			if (speedX_ < maxSpeedX_)
			{
				speedX_ += 0.5;
				if (speedX_ > maxSpeedX_)
				{
					speedX_ = maxSpeedX_;
				}
			}
			if (speedY_ > -maxSpeedY_)
			{
				speedY_ += 0.5;
				if (speedY_ < -maxSpeedY_)
				{
					speedY_ = -maxSpeedY_;
				}
			}
		}
	}

	/*if (currentKeyStates [SDL_SCANCODE_S] && (currentKeyStates [SDL_SCANCODE_D] ^ currentKeyStates [SDL_SCANCODE_A]))
	{
		c = sqrt(2);
		//c = sqrt(maxSpeedX_ * maxSpeedX_ + maxSpeedY_ * maxSpeedY_);
		maxSpeedX_ /= c;
		maxSpeedY_ /= c;
		if (currentKeyStates [SDL_SCANCODE_S] && currentKeyStates[SDL_SCANCODE_D])
		{
			if (speedX_ < maxSpeedX_)
			{
				speedX_ += 0.5;
				if (speedX_ > maxSpeedX_)
				{
					speedX_ = maxSpeedX_;
				}
			}
			if (speedY_ < maxSpeedY_)
			{
				speedY_ += 0.5;
				if (speedY_ > maxSpeedY_)
				{
					speedY_ = maxSpeedY_;
				}
			}
		}
		if (currentKeyStates [SDL_SCANCODE_S] && currentKeyStates [SDL_SCANCODE_A])
		{
			if (speedX_ < maxSpeedX_)
			{
				speedX_ += 0.5;
				if (speedX_ > maxSpeedX_)
				{
					speedX_ = maxSpeedX_;
				}
			}
			if (speedY_ > -maxSpeedY_)
			{
				speedY_ += 0.5;
				if (speedY_ < -maxSpeedY_)
				{
					speedY_ = -maxSpeedY_;
				}
			}
		}
	}*/

	if( currentKeyStates[ SDL_SCANCODE_W ] ^ currentKeyStates[ SDL_SCANCODE_S ])
	{
		if(currentKeyStates[ SDL_SCANCODE_S ])
			if(speedX_ < maxSpeedX_)
			{
				speedX_ += 1;
				if(speedX_ > maxSpeedX_)
					speedX_ = maxSpeedX_;
			}
			
		if(currentKeyStates[ SDL_SCANCODE_W ])
			if(speedX_ > -maxSpeedX_)
			{
				speedX_ -= 1;
				if(speedX_ < -maxSpeedX_)
					speedX_ = -maxSpeedX_;
			}
	}
	else if( speedX_ < 0 )
		speedX_ += 1;
	else if( speedX_ > 0 )
		speedX_ -= 1;
		
	
	if( currentKeyStates[ SDL_SCANCODE_A ] ^ currentKeyStates[ SDL_SCANCODE_D ])
	{
		if(currentKeyStates[ SDL_SCANCODE_D ])
			if(speedY_ < maxSpeedY_)
			{
				speedY_ += 1;
				if(speedY_ > maxSpeedY_)
					speedY_ = maxSpeedY_;
			}
			
		if(currentKeyStates[ SDL_SCANCODE_A ])
			if(speedY_ > -maxSpeedY_)
			{
				speedY_ -= 1;
				if(speedY_ < -maxSpeedY_)
					speedY_ = -maxSpeedY_;
			}
	}
	else if( speedY_ < 0 )
		speedY_ += 1;
	else if( speedY_ > 0 )
		speedY_ -=1;
}

void Player::update()
{
	if(speedX_ != 0 || speedY_ != 0)
	{
		targetPosX_ = posX_ + speedX_;
		targetPosY_ = posY_ + speedY_;
	}
}


void Player::collision(Entity* param)
{
	//do stuff
}


void NPC::update()
{
	//do stuff
}

void NPC::readInput()
{
	//do stuff
}

void NPC::collision(Entity* param)
{
	//do stuff
}


void Projectile::update()
{
	//do stuff
}

void Projectile::readInput()
{
	//do stuff
}

void Projectile::collision(Entity* param)
{
	//do stuff
}

//////////////////////////////
//	Static object
//////////////////////////////

void Wall::update()
{
	//do stuff
}

void Wall::collision(Entity* param)
{
	//do stuff
}


void Spawner::update()
{
	//do stuff
}

void Spawner::collision(Entity* param)
{
	//do stuff
}