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

void Map::makeCameraController(double maxSpeed, double acceleration)
{
	if( CameraController_ != nullptr)
		delete CameraController_;
	CameraController_ = new CameraController{maxSpeed, acceleration };
}

void Map::makeWall(double posX, double posY, unsigned width, unsigned height)
{
	walls_.push_back(new Wall{ posX, posY, width, height});
}

void Map::makeSpawner(double posX, double posY, unsigned width, unsigned height)
{
	spawners_.push_back(new Spawner{ posX, posY, width, height});
}

CameraController* Map::getCameraController()
{
	return CameraController_;
}

std::vector<Wall*>& Map::getWalls()
{
	return walls_;
}

std::vector<Spawner*>& Map::getSpawners()
{
	return spawners_;
}