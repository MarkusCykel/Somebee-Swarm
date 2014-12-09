#ifndef ENTITY_H
#define ENTITY_H

#include "classes.h"
#include <utility>
#include <SDL.h>
#include <math.h>
#include "Map.h"
#include "Controller.h"
#include "Timer.h"

//////////////////////////////
//	Entity
//////////////////////////////

class Entity
{
	public:
		Entity(int posX, int posY, unsigned width, unsigned height) : move_vector_{std::make_pair(0,0)}, posX_{posX}, posY_{posY}, width_{width}, height_{height} {};
	
		virtual void update() = 0;
		virtual void render(SDL_Renderer*, const SDL_Rect& camera) = 0;
		
		virtual void collision(Entity*) = 0;
		
		double getX();
		double getY();
		double getWidth() { return width_; }
		double getHeight() { return height_; }
		
	protected:
		double posX_;
		double posY_;
		unsigned width_;
		unsigned height_;
		std::pair<double,double> move_vector_;
};


//////////////////////////////
//	Live Objects 
//////////////////////////////

class Live_Object : public Entity
{
	public:
		Live_Object(int posX, int posY, unsigned width, unsigned height, double maxSpeed, double acceleration, unsigned angle) 
			:  speed_{0}, speedX_{0}, speedY_{0}, alive_{true}, targetPosX_{posX}, targetPosY_{posY}, maxSpeed_{maxSpeed}, acceleration_{acceleration}, angle_{angle}, Entity{posX, posY, width, height} {};
		
		virtual void collision(Entity*) = 0;
		
		double getTargetX();
		double getTargetY();
		bool getAlive();
		
		void setPosition(double x, double y);
		void setAlive(bool);
	protected:
		double targetPosX_, targetPosY_;
		double speedX_, speedY_;
		double speed_;
		double maxSpeed_;
		double acceleration_;
		unsigned angle_;
		bool alive_;
};


//////////////////////////////
//	Player
//////////////////////////////
class Player : public Live_Object
{
	public:
		Player(int posX, int posY, unsigned width, unsigned height, double maxSpeed, double acceleration)
			: Live_Object{posX, posY, width, height, maxSpeed, acceleration, 0} {};
		
		void readInput();
		void update();
		void render(SDL_Renderer*, const SDL_Rect& camera);
		void collision(Entity*);
};

class NPC : public Live_Object
{
	public:
		NPC(int posX, int posY, unsigned width, unsigned height, double maxSpeed, double acceleration, Map* map)
			: map_{map}, Live_Object{posX, posY, width, height, maxSpeed, acceleration, 0} {};
		
		void readInput();
		void update();
		void render(SDL_Renderer*, const SDL_Rect& camera);
		void collision(Entity*);
		
	private:
		Map* map_;
};

class Projectile : public Live_Object
{
	public:
		Projectile(int posX, int posY, unsigned width, unsigned height, double maxSpeed, double acceleration, unsigned angle)
			: Live_Object{posX, posY, width, height, maxSpeed, acceleration, angle} {}
		
		void readInput();
		void update();
		void render(SDL_Renderer*, const SDL_Rect& camera);
		void collision(Entity*);
};

class Spawner : public Live_Object
{
	public:
		Spawner(int posX, int posY, unsigned width, unsigned height, double maxSpeed, double acceleration, Map* map, Uint32 interval) : map_{map}, interval_{interval}, Live_Object{posX, posY, width, height, maxSpeed, acceleration, 0} { timer_.start(); };
		
		void readInput();
		void update();
		void render(SDL_Renderer*, const SDL_Rect& camera);
		void collision(Entity*);
	
	private:
		Timer timer_;
		Uint32 interval_;
		Map* map_;
};


//////////////////////////////
//	Static Objects	
//////////////////////////////

class Wall : public Entity
{
	public:
		Wall(int posX, int posY, unsigned width, unsigned height) : Entity{posX, posY, width, height} {};
		
		void update();
		void render(SDL_Renderer*, const SDL_Rect& camera);
		void collision(Entity*);
};

#endif