#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "classes.h"
#include <map>
#include "Entity.h"
#include "Map.h"

class Controller
{
	public:
		void update(Map& map);
	private:
		void checkCollisions(Map& map);
		
		std::map<LiveObject*,std::pair<double,double>> requestedPositions_;
};

#endif