#include "Map.h"
#include <map>

void Map::renderBackground(SDL_Renderer* renderer, const SDL_Rect& camera, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = { 0, 0, 1280, 960 };
	
	renderQuad.w = camera.w;
	renderQuad.h = camera.h;

	//Render to screen
	SDL_RenderCopyEx( renderer, background_, &camera, &renderQuad, angle, center, flip );
}


void Map::loadBackground(const std::string& path, SDL_Renderer* renderer)
{
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        background_ = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( background_ == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
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

void Map::readInput()
{
		player_->readInput();
		
		for( const auto &i : npcs_ )
		{
			i->readInput();
		}
		
		for( const auto &i : projectiles_ )
		{
			i->readInput();
		}
}

void Map::update()
{
		player_->update();
		
		for( const auto &i : npcs_ )
		{
			i->update();
		}
		
		for( const auto &i : projectiles_ )
		{
			i->update();
		}
}

void Map::render(SDL_Renderer* renderer, const SDL_Rect& camera)
{
	//Clear screen
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( renderer );
	
	player_->render(renderer, camera);
	
	for( auto i : npcs_ )
		i->render(renderer,camera);
		
	for( auto i : projectiles_)
		i->render(renderer,camera);
		
	//Update screen
	SDL_RenderPresent( renderer );
}

void Map::spawnEntity(const std::string& param, int posX, int posY, unsigned width, unsigned height, double maxSpeed, double acceleration, unsigned angle)
{
	static std::map<std::string,int> entity;
	entity["PLAYER"] = 1;
	entity["NPC"] = 2;
	entity["SPAWNER"] = 3;
	entity["PROJECTILE"] = 4;
	
		switch (entity[param])
		{
			case 1 :
				//delete player_;
				player_ = new Player{posX,posY,width,height,maxSpeed,acceleration};
				break;
			case 2 :
				npcs_.push_back(new NPC{posX,posY,width,height,maxSpeed,acceleration,this});
				break;
			case 4 :
				projectiles_.push_back(new Projectile(posX,posY,width,height,maxSpeed,acceleration,angle));
				break;
			default :
				std::cerr << "Invalid entity\n";
		}
}

Player* Map::getPlayer()
{
	return player_;
}

std::vector<NPC*> Map::getNpcs()
{
	return npcs_;
}

std::vector<Wall*> Map::getWalls()
{
	return walls_;
}

std::vector<Spawner*> Map::getSpawners()
{
	return spawners_;
}

std::vector<Projectile*> Map::getProjectiles()
{
	return projectiles_;
}