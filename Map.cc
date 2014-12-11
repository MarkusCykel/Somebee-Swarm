#include "Map.h"
#include <map>

void Map::loadBackground(const std::string& path, SDL_Renderer* renderer)
{
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	SDL_Surface* stretchedSurface = SDL_CreateRGBSurface(0,width_, height_,32,0,0,0,0);
	SDL_BlitScaled( loadedSurface, NULL , stretchedSurface, NULL);
	
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        background_ = SDL_CreateTextureFromSurface( renderer, stretchedSurface );
        if( background_ == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
        SDL_FreeSurface( stretchedSurface );
    }
}

double Map::getWidth()
{
	return width_;
}


double Map::getHeight()
{
	return height_;
}


void Map::renderBackground(SDL_Renderer* renderer, const SDL_Rect& camera, const int& window_width, const int& window_height)
{
	SDL_Rect renderQuad = { 0, 0, window_width, window_height };
	SDL_Rect cameratemp = { camera.x, camera.y, camera.w, camera.h };
	renderQuad.x = 0;
	renderQuad.y = 0;
	SDL_Rect black = {0,0,width_,height_};
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderFillRect(renderer, &black);
	
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
	
	SDL_RenderCopy( renderer, background_, &cameratemp, &renderQuad);
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

void Map::makePlayer(double posX, double posY, unsigned width, unsigned height, double maxSpeed, double acceleration)
{
	if( player_ != nullptr)
		delete player_;
	player_ = new Player{ posX, posY, width, height, maxSpeed, acceleration };
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
	projectiles_.push_back(new Projectile{ posX, posY, width, height, maxSpeed, acceleration, move_vector });
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