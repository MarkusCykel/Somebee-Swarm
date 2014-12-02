#include "Controller.h"

void Controller::update(Map& map)
{
	auto player = map.getPlayer();
	auto temp = player->getTargetPosition();
	player->setPosition(temp.first, temp.second);
}

void Controller::requestPosition(double x, double y, Live_Object* entity)
{
	requestedPositions_[entity] = std::make_pair(x,y);
}

void Controller::check_collisions()
{
	
}