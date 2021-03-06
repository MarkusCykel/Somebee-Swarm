#include "Map.h"
#include <map>

Map::~Map()
{
	delete player_;
	
	for(auto& i : npcs_)
	{
		delete i;
	}
	
	for(auto& i : projectiles_)
	{
		delete i;
	}
	
	for(auto& i : walls_)
	{
		delete i;
	}
	
	for(auto& i : spawners_)
	{
		delete i;
	}
	
	SDL_DestroyTexture( background_ );
}

void Map::loadBackground( SDL_Renderer* renderer, const std::string& path)
{
	background__.loadFromFileStretched( renderer, path, width_, height_ );
}


void Map::renderBackground(SDL_Renderer* renderer, const SDL_Rect& camera, const int& window_width, const int& window_height)
{
	SDL_Rect renderQuad = { 0, 0, window_width, window_height };
	SDL_Rect cameratemp = { camera.x, camera.y, camera.w, camera.h };
	renderQuad.x = 0;
	renderQuad.y = 0;
	
	if ( camera.y <= 0 )
	{
		cameratemp.y = 0;
		cameratemp.h += camera.y;
		renderQuad.y -= camera.y;
		renderQuad.h += camera.y;
	}
	else if ( camera.y + renderQuad.h >= height_ )
	{
		renderQuad.h -= window_height - (height_ - camera.y);
	}
	
	if ( camera.x <= 0 )
	{
		cameratemp.x = 0;
		cameratemp.w += camera.x;
		renderQuad.x -= camera.x;
		renderQuad.w += camera.x;
	}
	else if ( camera.x + renderQuad.w >= width_)
	{
		renderQuad.w -= window_width - (width_ - camera.x);
	}
	
	background__.render( renderer, &cameratemp, &renderQuad);
}

bool Map::cleanUp(unsigned& score)
{
	if(!player_->getAlive())
	{
		return true;
	}

	for(int i{0}; i < npcs_.size(); ++i)
	{
		if(!npcs_.at(i)->getAlive())
		{
			delete npcs_.at(i);
			npcs_.erase(npcs_.begin() + i);
			++score;
		}
	}
	
	for(int i{0}; i<projectiles_.size(); ++i)
	{
		if(!projectiles_.at(i)->getAlive())
		{
			delete projectiles_.at(i);
			projectiles_.erase(projectiles_.begin() + i);
		}
	}
	
	return false;
}

void Map::makePlayer(double posX, double posY, unsigned width, unsigned height, double maxSpeed, double acceleration, Uint32 rate_of_fire)
{
	if( player_ != nullptr)
		delete player_;
	player_ = new Player{ posX, posY, width, height, maxSpeed, acceleration, rate_of_fire };
}


void Map::makeSpawner(double posX, double posY, unsigned width, unsigned height, double maxSpeed, double acceleration, Uint32 interval)
{ 
	spawners_.push_back(new Spawner{ posX, posY, width, height, maxSpeed, acceleration, this, interval }); 
}


void Map::makeNPC(double posX, double posY, unsigned width, unsigned height, double maxSpeed, double acceleration)
{
	npcs_.push_back(new NPC{ posX, posY, width, height, maxSpeed, acceleration, this});
}


void Map::makeProjectile(double posX, double posY, unsigned width, unsigned height, double maxSpeed, double acceleration, std::pair<double,double> move_vector)
{
	projectiles_.push_back(new Projectile{ posX, posY, width, height, maxSpeed, move_vector });
}

void Map::makeWall(double posX, double posY, unsigned width, unsigned height)
{
	walls_.push_back(new Wall{ posX, posY, width, height});
}

Player* Map::getPlayer()
{
	return player_;
}


std::vector<NPC*>& Map::getNpcs()
{
	return npcs_;
}


std::vector<Wall*>& Map::getWalls()
{
	return walls_;
}


std::vector<Spawner*>& Map::getSpawners()
{
	return spawners_;
}


std::vector<Projectile*>& Map::getProjectiles()
{
	return projectiles_;
}