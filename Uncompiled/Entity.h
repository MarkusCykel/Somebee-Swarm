#ifndef ENTITY_H
#define ENTITY_H

#include "classes.h"
#include <utility>
#include <SDL.h>
#include <math.h>
#include "Map.h"
#include "Timer.h"
#include "Texture.h"
#include <iostream>

//////////////////////////////
//	Entity
//////////////////////////////

class Entity
{
	public:
		Entity(int posX, int posY, unsigned width, unsigned height);
		
		virtual void render(SDL_Renderer*, const SDL_Rect& camera) = 0;
		
		const int& getX() const;
		const int& getY() const;
		
		void setPosition(const double& x, const double& y);
		
		double getWidth() { return collisionBox_.w; }
		double getHeight() { return collisionBox_.h; }
		
		SDL_Rect getCollisionbox() { return collisionBox_; }
		
		SDL_Rect getBox() = delete;
		
	private:
		SDL_Rect collisionBox_;
};


//////////////////////////////
//	Live Objects 
//////////////////////////////

class LiveObject : public Entity
{
	public:
		LiveObject(int posX, int posY, unsigned width, unsigned height, double speed, double acceleration) 
			: targetPosX_{posX}, targetPosY_{posY}, speed_{speed}, acceleration_{acceleration}, alive_{true}, Entity{posX, posY, width, height} {}
		
		int getTargetX() { return targetPosX_; }
		int getTargetY() { return targetPosY_; }
		
		bool getAlive();
		void setAlive(bool);
		
	protected:
		bool entityCollision(Entity*);
		bool entityCollisionCheck(Entity*);
		bool boundryBoxCollision(const Map&);
		bool boundryBoxCollisionCheck(const Map&);
	
		double moveCapacityX_{0}, moveCapacityY_{0};
		double acceleration_;
		double targetPosX_, targetPosY_;
		double speed_;
		
		bool alive_;
};


//////////////////////////////
//	Player
//////////////////////////////

class Player : public LiveObject
{
	public:
		Player(int posX, int posY, unsigned width, unsigned height, double maxSpeed, double acceleration, Uint32 rate_of_fire)
			: move_vector_{std::make_pair(0,0)}, rate_of_fire_{rate_of_fire}, LiveObject{posX, posY, width, height, maxSpeed, acceleration} {};
		
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

class NPC : public LiveObject
{
	public:
		NPC(int posX, int posY, unsigned width, unsigned height, double maxSpeed, double acceleration, Map* map)
			: map_{map}, LiveObject{posX, posY, width, height, maxSpeed, acceleration } {};
			
		void readInput();
		void update(Map&);
		void render(SDL_Renderer*, const SDL_Rect& camera);
		
		static void loadTexture(SDL_Renderer* renderer, const std::string& path );
		
		void checkCollisions(Map& map);
	private:
		static Texture texture_;
		Map* map_;
};

class Projectile : public LiveObject
{
	public:
		Projectile(int posX, int posY, unsigned width, unsigned height, double speed, std::pair<double,double> move_vector)
			: move_vector_{move_vector}, LiveObject{posX, posY, width, height, speed, speed} {}
		
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
		Spawner(int posX, int posY, unsigned width, unsigned height, double speed, double acceleration, Map* map, Uint32 interval) : map_{map}, interval_{interval}, LiveObject{posX, posY, width, height, speed, acceleration} { timer_.start(); };
		
		static void loadTexture( SDL_Renderer* renderer, const std::string& path );
		
		void readInput();
		void update(Map&);
		void render(SDL_Renderer*, const SDL_Rect& camera);
	
	private:
		Timer timer_;
		Uint32 interval_;
		
		static Texture texture_;
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