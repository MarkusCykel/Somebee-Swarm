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
		Entity(double posX, double posY, double width, double height) : posX_{posX}, posY_{posY}, width_{width}, height_{height}, alive_{true} {};
	
		void render(SDL_Renderer*, const SDL_Rect& camera);
		
		virtual void update() = 0;
		virtual void collision(Entity*) = 0;
		
		double getX();
		double getY();
		double getWidth() { return width_; }
		double getHeihgt() { return height_; }
		bool getAlive();
		void setAlive(bool);
		
	protected:
		double posX_;
		double posY_;
		double width_;
		double height_;
		bool alive_;
};


//////////////////////////////
//	Live Objects 
//////////////////////////////

class Live_Object : public Entity
{
	public:
		Live_Object(double posX, double posY, double width, double height) 
			: maxSpeedX_{5}, maxSpeedY_{5}, targetPosX_{posX}, targetPosY_{posY}, speedX_{0}, speedY_{0}, Entity{posX, posY, width, height} {};
		virtual void readInput( ) = 0;
		void setPosition(double x, double y);
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
		Player(double posX, double posY, double width, double height) : Live_Object{posX, posY, width, height} {};
		void readInput();
		void update();
		void collision(Entity*);
};

class NPC : public Live_Object
{
	public:
		NPC(double posX, double posY, double width, double height) : Live_Object{posX, posY, width, height} {};
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
		Wall(double posX, double posY, double width, double height) : Entity{posX, posY, width, height} {};
		
		void update();
		void collision(Entity*);
};

class Spawner : public Entity
{
	public:
		Spawner(double posX, double posY, double width, double height) : Entity{posX, posY, width, height} {};
		
		void update();
		void collision(Entity*);
};

#endif