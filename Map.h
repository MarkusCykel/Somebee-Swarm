#ifndef MAP_H
#define MAP_H

#include "Entity.h"
#include "Controller.h"
#include <vector>
#include <iostream>

class Map
{
	public:
		Map(unsigned width, unsigned height) 
			: width_{width}, height_{height} {}
			
		double getWidth();
		double getHeight();
		
		void readInput();
		void update();
		void render(SDL_Renderer*, const SDL_Rect&);
		void spawnEntity(const std::string& entity, double x, double y, double width, double height);
		Player* getPlayer();
		std::vector<NPC*> getNpcs();
		std::vector<Wall*> getWalls();
		std::vector<Spawner*> getSpawners();
		
	private:
		Player* player_;
		std::vector<NPC*> npcs_;
		std::vector<Projectile*> projectiles_;
		std::vector<Wall*> walls_;
		std::vector<Spawner*> spawners_;
		
		double width_;
		double height_;
};

#endif