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
		void requestPosition(double x, double y, Live_Object*);
	private:
		void check_collisions();
		
		std::map<Live_Object*,std::pair<double,double>> requestedPositions_;
};

#endif