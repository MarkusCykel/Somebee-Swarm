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
		Entity(int posX, int posY, unsigned width, unsigned height) : posX_{posX}, posY_{posY}, width_{width}, height_{height} {};
	
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
};


//////////////////////////////
//	Live Objects 
//////////////////////////////

class LiveObject : public Entity
{
	public:
		LiveObject(int posX, int posY, unsigned width, unsigned height, double maxSpeed, double acceleration) 
			:  speed_{0}, speedX_{0}, speedY_{0}, alive_{true}, targetPosX_{posX}, targetPosY_{posY}, maxSpeed_{maxSpeed}, acceleration_{acceleration}, Entity{posX, posY, width, height} {};
		
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
		bool alive_;
};


//////////////////////////////
//	Player
//////////////////////////////
class Player : public LiveObject
{
	public:
		Player(int posX, int posY, unsigned width, unsigned height, double maxSpeed, double acceleration)
			: move_vector_{std::make_pair(0,0)}, LiveObject{posX, posY, width, height, maxSpeed, acceleration} {};
		
		void readInput();
		void update();
		void render(SDL_Renderer*, const SDL_Rect& camera);
		void collision(Entity*);
		void fire(Map&, double targetX, double targetY);
	private:
		std::pair<double,double> move_vector_;
		Timer timer_;
};

class NPC : public LiveObject
{
	public:
		NPC(int posX, int posY, unsigned width, unsigned height, double maxSpeed, double acceleration, Map* map)
			: map_{map}, LiveObject{posX, posY, width, height, maxSpeed, acceleration } {};
		
		void readInput();
		void update();
		void render(SDL_Renderer*, const SDL_Rect& camera);
		void collision(Entity*);
		
	private:
		Map* map_;
};

class Projectile : public LiveObject
{
	public:
		Projectile(int posX, int posY, unsigned width, unsigned height, double maxSpeed, double acceleration, std::pair<double,double> move_vector)
			: move_vector_{move_vector}, LiveObject{posX, posY, width, height, maxSpeed, acceleration } {}
		
		void readInput();
		void update();
		void render(SDL_Renderer*, const SDL_Rect& camera);
		void collision(Entity*);
	private:
		std::pair<double,double> move_vector_;
};

class Spawner : public LiveObject
{
	public:
		Spawner(int posX, int posY, unsigned width, unsigned height, double maxSpeed, double acceleration, Map* map, Uint32 interval) : map_{map}, interval_{interval}, LiveObject{posX, posY, width, height, maxSpeed, acceleration} { timer_.start(); };
		
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