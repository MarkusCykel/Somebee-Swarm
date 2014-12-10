#include "Map.h"
#include <map>

void Map::render(SDL_Renderer* renderer, const SDL_Rect& camera)
{	
	player_->render(renderer, camera);
	
	for( auto i : npcs_ )
		i->render(renderer,camera);
		
	for( auto i : projectiles_)
		i->render(renderer,camera);
		
	//Update screen
	SDL_RenderPresent( renderer );
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
	if( camera.y < 1 && camera.x < 1 )
	{
		cameratemp.x = 0;
		cameratemp.y = 0;
		renderQuad.x -= camera.x;
		renderQuad.y -= camera.y;
		SDL_RenderCopy( renderer, background_, &cameratemp, &renderQuad);
	}
	else if( camera.x < 1 && camera.y <= renderQuad.h && camera.y > 0)
	{
		cameratemp.x = 0;
		renderQuad.x -= camera.x;
		SDL_RenderCopy( renderer, background_, &cameratemp, &renderQuad);
	}
	else if( camera.y < 1 && camera.x <= renderQuad.w && camera.x > 0 )
	{
		cameratemp.y = 0;
		renderQuad.y -= camera.y;
		SDL_RenderCopy( renderer, background_, &cameratemp, &renderQuad);
	}
	else if( camera.x > renderQuad.w && camera.y <= renderQuad.h && camera.y > 0 )
	{
		cameratemp.x = renderQuad.w;
		renderQuad.x -= camera.x - renderQuad.w;
		SDL_RenderCopy( renderer, background_, &cameratemp, &renderQuad);
	}
	else if( camera.y > renderQuad.h && camera.x <= renderQuad.w && camera.x > 0 )
	{
		cameratemp.y = renderQuad.h;
		renderQuad.y -= camera.y - renderQuad.h;
		SDL_RenderCopy( renderer, background_, &cameratemp, &renderQuad);
	}
	else if( camera.x < 1 && camera.y > renderQuad.h )
	{
		cameratemp.x = 0;
		cameratemp.y = renderQuad.h;
		renderQuad.x -= camera.x;
		renderQuad.y -= camera.y - renderQuad.h;
		SDL_RenderCopy( renderer, background_, &cameratemp, &renderQuad);
	}
	else if( camera.y < 1 && camera.x > renderQuad.w )
	{
		cameratemp.y = 0;
		cameratemp.x = renderQuad.w;
		renderQuad.y -= camera.y;
		renderQuad.x -= camera.x - renderQuad.w;
		SDL_RenderCopy( renderer, background_, &cameratemp, &renderQuad);
	}
	else if( camera.x > renderQuad.w && camera.y > renderQuad.h )
	{
		cameratemp.x = renderQuad.w;
		cameratemp.y = renderQuad.h;
		renderQuad.x += renderQuad.w - camera.x;
		renderQuad.y += renderQuad.h - camera.y;
		SDL_RenderCopy( renderer, background_, &cameratemp, &renderQuad);
	}
	else
	{
		SDL_RenderCopy( renderer, background_, &cameratemp, &renderQuad);
	}
	std::cout<<"Camera x:"<<camera.x<<" Camera y:"<<camera.y<<std::endl;
	std::cout<<"Cameratemp x:"<<cameratemp.x<<" Cameratemp y:"<<cameratemp.y<<std::endl;
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
		
		for( const auto &i : spawners_ )
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