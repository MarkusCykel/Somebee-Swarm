#ifndef MAPEDITCAMERACONTROLLER_H
#define MAPEDITCAMERACONTROLLER_H

#include "MapEditclasses.h"
#include <utility>
#include <SDL.h>
#include <math.h>
#include "MapEditMap.h"
#include "MapEditTimer.h"

class MapEditCameraController
{
	public:
		MapEditCameraController(double maxSpeed, double acceleration)
			: move_vector_{std::make_pair(0,0)}, posX_{0}, posY_{0}, targetPosX_{0}, targetPosY_{0}, speedX_{0}, speedY_{0}, speed_{0}, maxSpeed_{maxSpeed}, acceleration_{acceleration} {};
		
		void setPosition(double x, double y);
		double getTargetX();
		double getTargetY();
		void readInput();
		void update(MapEditMap&);
		double getX();
		double getY();
		
	private:
		std::pair<double,double> move_vector_;
		MapEditTimer timer_;
		double posX_;
		double posY_;
		double targetPosX_, targetPosY_;
		double speedX_, speedY_;
		double speed_;
		double maxSpeed_;
		double acceleration_;
};

#endif