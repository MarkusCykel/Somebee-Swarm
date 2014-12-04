#ifndef ENTITY_H
#define ENTITY_H

#include "classes.h"
#include <utility>
#include <SDL.h>
#include "Controller.h"

//////////////////////////////
//	Entity
//////////////////////////////

class Entity
{
	public:
		Entity(double param, double param2) : posX_{param}, posY_{param2}, alive_{true} {};
	
		void render();
		
		virtual void update() = 0;
		virtual void collision(Entity*) = 0;
		
		double getX();
		double getY();
		bool getAlive();
		void setAlive(bool);
		
	protected:
		double posX_;
		double posY_;
		bool alive_;
};


//////////////////////////////
//	Live Objects 
//////////////////////////////

class Live_Object : public Entity
{
	public:
		Live_Object(double param, double param2) 
			: maxSpeedX_{5}, maxSpeedY_{5}, speedX_{0}, speedY_{0}, Entity(param, param2) {};
		virtual void readInput( ) = 0;
		void setPosition(double, double);
		double getTargetX();
		double getTargetY();
	protected:
		double speedX_, speedY_;
		double maxSpeedX_, maxSpeedY_;
		double targetPosX_;
		double targetPosY_;
};

class Player : public Live_Object
{
	public:
		Player(double param, double param2) : Live_Object(param, param2) {};
		void readInput();
		void update();
		void collision(Entity*);
};

class NPC : public Live_Object
{
	public:
		void readInput();
		void update();
		void collision(Entity*);
};

class Projectile : public Live_Object
{
	public:
		void readInput();
		void update();
		void collision(Entity*);
};


//////////////////////////////
//	Static Objects	
//////////////////////////////

class Wall : public Entity
{
	public:
		Wall(double param, double param2) : Entity{param,param2} {};
		
		void update();
		void collision(Entity*);
};

class Spawner : public Entity
{
	public:
		Spawner(double param, double param2) : Entity{param,param2} {};
		
		void update();
		void collision(Entity*);
};

#endif