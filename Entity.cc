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
	//do stuff
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