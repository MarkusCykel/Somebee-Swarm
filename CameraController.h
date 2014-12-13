#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include "classes.h"
#include <utility>
#include <SDL.h>
#include <math.h>
#include "Map.h"
#include "Timer.h"

class CameraController
{
	public:
		CameraController(double maxSpeed, double acceleration)
			: move_vector_{std::make_pair(0,0)}, posX_{0}, posY_{0}, maxSpeed_{maxSpeed}, acceleration_{acceleration} {};
		
		void setPosition(double x, double y);
		double getTargetX();
		double getTargetY();
		void readInput();
		void update(Map&);
		double getX();
		double getY();
		
	private:
		std::pair<double,double> move_vector_;
		Timer timer_;
		double posX_;
		double posY_;
		double targetPosX_, targetPosY_;
		double speedX_, speedY_;
		double speed_;
		double maxSpeed_;
		double acceleration_;
};

#endif