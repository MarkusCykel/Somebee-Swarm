#include "Entity.h"
#include <iostream>
#include <iomanip>

#define PI 3.14159265

//////////////////////////////
//	Entity
//////////////////////////////

const int& Entity::getX() const
{
	return posX_;
}

const int& Entity::getY() const
{
	return posY_;
}


//////////////////////////////
//	Live Object
//////////////////////////////

void Entity::setPosition(const double& x, const double& y)
{
	posX_ = x;
	posY_ = y;
}

bool LiveObject::getAlive()
{
	return alive_;
}

void LiveObject::setAlive(bool alive)
{
	alive_ = alive;
}

bool LiveObject::entityCollisionCheck(Entity* npc)
{
	double leftA, leftB;
	double rightA, rightB;
	double bottomA, bottomB;
	double topA, topB;
	
	leftA = getX();
	rightA = getX() + getWidth();
	topA = getY();
	bottomA = getY() + getHeight();

	leftB =  npc->getX();
	rightB = npc->getWidth() + npc->getX();
	topB =   npc->getY();
	bottomB =  npc->getHeight() + npc->getY();

	if((bottomA >= topB && topB >= topA || bottomB >= topA && topA >= topB) && (rightA >= leftB && rightB >= leftA || leftA <= rightB && rightA >= rightB))
	{
		return true;
	}
	
	return false;
}


bool LiveObject::entityCollision(Entity* character)
{
	bool collided{false};
	
	double leftA, leftB;
	double rightA, rightB;
	double bottomA, bottomB;
	double topA, topB;
	
	double prevLeftA = getX();
	double prevRightA = getX() + getWidth();
	double prevTopA = getY();
	double prevBottomA = getY() + getHeight();
	

	leftA = getTargetX();
	rightA = getTargetX() + getWidth();
	topA = getTargetY();
	bottomA = getTargetY() + getHeight();
	
		
	leftB = character->getX();
	rightB = character->getX() + character->getWidth() ;
	topB = character->getY();
	bottomB = character->getY() + character->getHeight() ;

	if(!(topA >= bottomB || bottomA <= topB || leftA >= rightB || rightA <= leftB)) // if it collided
	{
		double moveCapacityY = abs(moveCapacityY_);
		double moveCapacityX = abs(moveCapacityX_);
		
		if( prevBottomA <= topB && prevRightA <= leftB ) // top left corner
		{
			if( moveCapacityX < moveCapacityY ) // faster X than Y
			{
				targetPosX_ =  leftB - getWidth();
				moveCapacityX_ = 0;
			}
			else
			{
				targetPosY_ = topB - getHeight();
				moveCapacityY_ = 0;
			}
		}
		else if( prevBottomA <= topB && prevLeftA  >= rightB ) // top right corner
		{
			if( moveCapacityX < moveCapacityY ) // faster X than Y
			{
				targetPosX_ =  rightB;
				moveCapacityX_ = 0;
			}
			else
			{
				targetPosY_ = topB - getHeight();
				moveCapacityY_ = 0;
			}
		}
		else if( prevTopA >= bottomB && prevRightA <= leftB ) // bottom left corner
		{
			if( moveCapacityX < moveCapacityY ) // faster X than Y
			{
				targetPosX_ =  leftB - getWidth();
				moveCapacityX_ = 0;
			}
			else
			{
				targetPosY_ = bottomB;
				moveCapacityY_ = 0;
			}
		}
		else if( prevTopA >= bottomB && prevLeftA  >= rightB ) // bottom right corner
		{
			if( moveCapacityX < moveCapacityY ) // faster X than Y
			{
				targetPosX_ =  rightB;
				moveCapacityX_ = 0;
			}
			else
			{
				targetPosY_ = bottomB;
				moveCapacityY_ = 0;
			}
		}
		else if( prevBottomA <= topB ) // from above
		{
			targetPosY_ = topB - getHeight();
			moveCapacityY_ = 0;
		}
		else if( prevTopA >= bottomB ) // from below
		{
			targetPosY_ = bottomB;
			moveCapacityY_ = 0;
		}
		else if( prevRightA <= leftB ) //from the left
		{
			targetPosX_ =  leftB - getWidth();
			moveCapacityX_ = 0;
		}	
		else if( prevLeftA  >= rightB ) // from the right
		{
			targetPosX_ = rightB;
			moveCapacityX_ = 0;
		}
		
		leftA = getTargetX();
		rightA = getTargetX() + getWidth();
		topA = getTargetY();
		bottomA = getTargetY() + getHeight();
		
		collided = true;
	}
	
	return collided;
}

bool LiveObject::boundryBoxCollision(const Map& map)
{
	if( targetPosX_ + getWidth() > map.getWidth())
	{
		targetPosX_ = map.getWidth() - getWidth();
		moveCapacityX_ = 0;
	}
	else if( targetPosX_ < 0  )
	{
		targetPosX_ = 0;
		moveCapacityX_ = 0;
	}
	
	if(  targetPosY_ > map.getHeight() - getHeight() )
	{
		targetPosY_ = map.getHeight() - getHeight();
		moveCapacityY_ = 0;
	}
	else if( targetPosY_ < 0)
	{
		targetPosY_ = 0;
		moveCapacityY_ = 0;
	}
}

bool LiveObject::boundryBoxCollisionCheck(const Map& map)
{
	if( targetPosX_ + getWidth() > map.getWidth())
	{
		return true;
	}
	
	if( targetPosX_ < 0  )
	{
		return true;
	}
	
	if(  targetPosY_ > map.getHeight() - getHeight() )
	{
		return true;
	}
	
	if( targetPosY_ < 0)
	{
		return true;
	}
	
	return false;
}


//////////////////////////////
//	Player
//////////////////////////////

void Player::readInput()
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
	
	if( currentKeyStates[ SDL_SCANCODE_W ] ^ currentKeyStates[ SDL_SCANCODE_S ] )
	{
		if(currentKeyStates[ SDL_SCANCODE_W ]) // If it was S, increase speed on x-axis
		{
			if(moveCapacityY_ > -speed_)
				moveCapacityY_ -= acceleration_;
			else
				moveCapacityY_ = -speed_;
		}
		else if(currentKeyStates[ SDL_SCANCODE_S ])
		{
			if(moveCapacityY_ < speed_)
				moveCapacityY_ += acceleration_;
			else
				moveCapacityY_ = speed_;
		}
	}
	else if( moveCapacityY_ < 0 ) // If W nor S is held down (or both), deaccelerate
		moveCapacityY_ += acceleration_;
	else if( moveCapacityY_ > 0 )
		moveCapacityY_ -= acceleration_;
	
	if( currentKeyStates[ SDL_SCANCODE_A ] ^ currentKeyStates[ SDL_SCANCODE_D ] )
	{
		if( currentKeyStates[ SDL_SCANCODE_A ] ) // If it was S, increase speed on x-axis
		{
			if(moveCapacityX_ > -speed_)
				moveCapacityX_ -= acceleration_;
			else
				moveCapacityX_ = -speed_;
		}
		else if( currentKeyStates[ SDL_SCANCODE_D ] )
		{
			if(moveCapacityX_ < speed_)
				moveCapacityX_ += acceleration_;
			else
				moveCapacityX_ = speed_;
		}
	}
	else if( moveCapacityX_ < 0 )
		moveCapacityX_ += acceleration_;
	else if( moveCapacityX_ > 0 )
		moveCapacityX_ -= acceleration_;
	
	
	std::pair<double,double> move_vector{ std::make_pair(moveCapacityX_, moveCapacityY_) };
	
	double vector_length = sqrt(pow(move_vector.first,2) + pow(move_vector.second, 2));
	
	if(vector_length != 0)
	{
		move_vector_.first = move_vector.first/vector_length;
		move_vector_.second = move_vector.second/vector_length;
	}
}

void Player::update(Map& map)
{
	if(abs(moveCapacityX_) > abs(moveCapacityY_))
	{
		targetPosX_ = getX() + move_vector_.first * abs(moveCapacityX_);
		targetPosY_ = getY() + move_vector_.second * abs(moveCapacityX_);
	}
	else
	{
		targetPosX_ = getX() + move_vector_.first * abs(moveCapacityY_);
		targetPosY_ = getY() + move_vector_.second * abs(moveCapacityY_);
	}
	
	checkCollisions(map);
	setPosition(targetPosX_, targetPosY_);
}

void Player::render(SDL_Renderer* renderer, const SDL_Rect & camera)
{
	SDL_Rect fillRect = { getX() - camera.x, getY() - camera.y, getHeight(), getWidth()};
	SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0x00, 0xFF );
	SDL_RenderFillRect( renderer, &fillRect );
}

/* Declares what happens when Player collides with another Entity */
void Player::checkCollisions(Map& map)
{
	boundryBoxCollision(map);

	auto walls = map.getWalls();
	for(auto i : walls)
	{
		entityCollision(i);
	}
	
	auto npcs  = map.getNpcs();
	for(auto i : npcs)
	{
		if(entityCollisionCheck(i))
			setAlive(false);
	}
}

void Player::fire(Map& map, double targetX, double targetY)
{
	std::pair<double,double> move_vector{ std::make_pair(targetX - getX(), targetY - getY()) };
	
	double vector_length = sqrt(pow(move_vector.first,2) + pow(move_vector.second, 2));
	
	if(vector_length != 0)
	{
		move_vector.first = move_vector.first/vector_length;
		move_vector.second = move_vector.second/vector_length;
		
		if(timer_.getTicks() > 1000/(rate_of_fire_))
		{
			timer_.stop();
		}
			
		if(!timer_.isStarted())
		{
			map.makeProjectile(getX() + getWidth()/2, getY() + getWidth()/2, 5, 5, 20, 20, move_vector);
			timer_.start();
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
	
	std::pair<double,double> move_vector{ std::make_pair(targetX - getX(), targetY - getY()) };
	
	double vector_length = sqrt(pow(move_vector.first,2) + pow(move_vector.second, 2));
	
	if(vector_length != 0)
	{
		move_vector.first = move_vector.first/vector_length;
		move_vector.second = move_vector.second/vector_length;
		
		if(abs(targetX - getX()) <= abs(move_vector.first * speed_) && abs(targetY - getY()) <= abs(move_vector.second * speed_))
		{
			targetPosX_ = targetX;
			targetPosY_ = targetY;
		}
		else
		{
			targetPosX_ = getX() + move_vector.first * speed_;
			targetPosY_ = getY() + move_vector.second * speed_;
		}
		
	}
}

void NPC::update(Map& map)
{
	checkCollisions(map);
	
	setPosition(targetPosX_, targetPosY_);
}


void NPC::render(SDL_Renderer* renderer, const SDL_Rect & camera)
{
	//Render red filled quad
	SDL_Rect fillRect = { getX() - camera.x, getY() - camera.y, getHeight(), getWidth()};
	SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );
	SDL_RenderFillRect( renderer, &fillRect );
}


void NPC::checkCollisions(Map& map)
{
	boundryBoxCollision(map);
	
	auto npcs = map.getNpcs();
	for(auto i : npcs)
		entityCollision(i);
 	auto walls = map.getWalls();
	for(auto i : walls)
		entityCollision(i);
}

/* It shouldn't have any input? */
void Projectile::readInput()
{
	targetPosX_ = getX() + move_vector_.first * speed_;
	targetPosY_ = getY() + move_vector_.second * speed_;
}

/* Update position depending on speed and  */
void Projectile::update(Map& map)
{
	if( targetPosX_ > map.getWidth() - getWidth() || targetPosX_ < 0 || targetPosY_ > map.getHeight() - getHeight() || targetPosY_ < 0 )
	{
		setAlive(false);
	}
	
	checkCollisions(map);
	
	setPosition(targetPosX_, targetPosY_);
}

void Projectile::render(SDL_Renderer* renderer, const SDL_Rect & camera)
{
	//Render red filled quad
	SDL_Rect fillRect = { getX() - int(camera.x + getHeight()/2), getY() - int(camera.y + getWidth()/2) , getHeight(), getWidth()};
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0x00, 0xFF );
	SDL_RenderFillRect( renderer, &fillRect );
}

/* Determines what happens to Projectile when it collides with another Entity */
void Projectile::checkCollisions(Map& map)
{		
	auto npcs  = map.getNpcs ();
	auto walls = map.getWalls();
	
	for(int i{1}; i <= speed_; ++i)
	{
		targetPosX_ = getX() + move_vector_.first*i;
		targetPosY_ = getY() + move_vector_.second*i;
		
		for( auto i: walls )
		{
			if(getAlive() && entityCollision(i))
			{
				setAlive(false);
			}
		}
	}
	
	for( auto i: npcs )
	{
		if(getAlive() && i->getAlive() && entityCollisionCheck(i))
		{
			setAlive(false);
			i->setAlive(false);
		}
	}
}

//////////////////////////////
//	Wall
//////////////////////////////

void Wall::render(SDL_Renderer* renderer, const SDL_Rect & camera)
{
	//Render red filled quad
	SDL_Rect fillRect = { getX() - camera.x, getY() - camera.y, getWidth(), getHeight()};
	SDL_SetRenderDrawColor( renderer, 0x5F, 0x5F, 0x5F, 0xFF );
	SDL_RenderFillRect( renderer, &fillRect );
}


//////////////////////////////
//	Spawner
//////////////////////////////

void Spawner::update(Map& map)
{
	if(timer_.getTicks() > interval_)
	{
		map.makeNPC(getX(), getY(), getWidth(), getHeight(), speed_, acceleration_);
		timer_.start();
	}
	//do stuff
}

void Spawner::render(SDL_Renderer* renderer, const SDL_Rect & camera)
{
	//Render red filled quad
	SDL_Rect fillRect = { getX() - camera.x, getY() - camera.y , getHeight(), getWidth()};
	SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0xFF, 0xFF );
	SDL_RenderFillRect( renderer, &fillRect );
}

//////////////////////////////
//	Help functions
//////////////////////////////