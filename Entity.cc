#include "Entity.h"

//////////////////////////////
//	Entity
//////////////////////////////

void Entity::render()
{
	//do something
}

std::pair<unsigned, unsigned> Entity::get_position()
{
	return position_;
}

bool Entity::get_alive()
{
	return alive_;
}

void Entity::set_alive(bool param)
{
	alive_ = param;
}

//////////////////////////////
//	Live Object
//////////////////////////////

void Player::update()
{
	//do stuff
}

void Player::read_input()
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
	
	if(currentKeyStates[ SDL_SCANCODE_W ])
		if(position_.first < 2500)
			position_.first = position_.first+1;
		
	if(currentKeyStates[ SDL_SCANCODE_S ])
		if(position_.first > 0)
			position_.first = position_.first-1;
		
	if(currentKeyStates[ SDL_SCANCODE_D])
		if(position_.second < 2500)
			position_.second = position_.second+1;
		
	if(currentKeyStates[ SDL_SCANCODE_A ])
		if(position_.second > 0)
			position_.second = position_.second-1;
}

void Player::collision(Entity* param)
{
	//do stuff
}


void NPC::update()
{
	//do stuff
}

void NPC::read_input()
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

void Projectile::read_input()
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