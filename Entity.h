#ifndef ENTITY_H
#define ENTITY_H

#include "classes.h"
#include <utility>
#include <SDL.h>
#include <math.h>
#include "Map.h"
#include "Controller.h"
#include "Timer.h"
#include <iostream>

//////////////////////////////
//	Entity
//////////////////////////////

class Entity
{
	public:
		Entity(int posX, int posY, unsigned width, unsigned height) : posX_{posX}, posY_{posY}, width_{width}, height_{height} {};
		
		virtual void render(SDL_Renderer*, const SDL_Rect& camera) = 0;
		
		
		const int& getX() const;
		const int& getY() const;
		
		void setPosition(const double& x, const double& y);
		
		double getWidth() { return width_; }
		double getHeight() { return height_; }
		
		SDL_Rect getBox() = delete;
		
	private:
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
		LiveObject(int posX, int posY, unsigned width, unsigned height, double speed) 
			: targetPosX_{posX}, targetPosY_{posY}, speed_{speed}, alive_{true}, Entity{posX, posY, width, height} {}
		
		int getTargetX() { return targetPosX_; }
		int getTargetY() { return targetPosY_; }
		
		bool getAlive();
		void setAlive(bool);
		
	protected:
		bool npcCollision(NPC*);
		
		double targetPosX_, targetPosY_;
		double speed_;
		
		bool alive_;
};

class Character : public LiveObject
{
	public:
		Character(int posX, int posY, unsigned width, unsigned height, double speed, double acceleration)
			: acceleration_{acceleration}, LiveObject{posX, posY, width, height, speed} {}
	
	protected:
		bool wallCollision(Wall*);
	
		double moveCapacityX_, moveCapacityY_;
		double acceleration_;
};


//////////////////////////////
//	Player
//////////////////////////////

class Player : public Character
{
	public:
		Player(int posX, int posY, unsigned width, unsigned height, double maxSpeed, double acceleration, Uint32 rate_of_fire)
			: move_vector_{std::make_pair(0,0)}, rate_of_fire_{rate_of_fire}, Character{posX, posY, width, height, maxSpeed, acceleration} {};
		
		void readInput();
		void update(Map&);
		void render(SDL_Renderer*, const SDL_Rect& camera);
		
		void checkCollisions(Map& map);
		void fire(Map&, double targetX, double targetY);
	private:
		std::pair<double,double> move_vector_;
		Uint32 rate_of_fire_;
		Timer timer_;
};

class NPC : public Character
{
	public:
		NPC(int posX, int posY, unsigned width, unsigned height, double maxSpeed, double acceleration, Map* map)
			: map_{map}, Character{posX, posY, width, height, maxSpeed, acceleration } {};
		
		void readInput();
		void update(Map&);
		void render(SDL_Renderer*, const SDL_Rect& camera);
		
		void checkCollisions(Map& map);
	private:
		Map* map_;
};

class Projectile : public LiveObject
{
	public:
		Projectile(int posX, int posY, unsigned width, unsigned height, double speed, std::pair<double,double> move_vector)
			: move_vector_{move_vector}, LiveObject{posX, posY, width, height, speed} {}
		
		void readInput();
		void update(Map&);
		void render(SDL_Renderer*, const SDL_Rect& camera);
		
		void checkCollisions(Map& map);
	private:
		bool wallCollision(Wall*);
		
		std::pair<double,double> move_vector_;
};

class Spawner : public LiveObject
{
	public:
		Spawner(int posX, int posY, unsigned width, unsigned height, double speed, double acceleration, Map* map, Uint32 interval) : acceleration_{acceleration}, map_{map}, interval_{interval}, LiveObject{posX, posY, width, height, speed} { timer_.start(); };
		
		void readInput();
		void update(Map&);
		void render(SDL_Renderer*, const SDL_Rect& camera);
	
	private:
		double acceleration_;
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
		
		void render(SDL_Renderer*, const SDL_Rect& camera);
};

#endif