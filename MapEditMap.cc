#include "MapEditMap.h"
#include <map>

void MapEditMap::loadBackground(const std::string& path, SDL_Renderer* renderer)
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

MapEditMap::~MapEditMap()
{
	delete CameraController_;
	delete playerspawner_;
	
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

double MapEditMap::getWidth()
{
	return width_;
}


double MapEditMap::getHeight()
{
	return height_;
}


void MapEditMap::renderBackground(SDL_Renderer* renderer, const SDL_Rect& camera, const int& window_width, const int& window_height)
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

void MapEditMap::makeCameraController(double maxSpeed, double acceleration)
{
	if( CameraController_ != nullptr)
		delete CameraController_;
	CameraController_ = new MapEditCameraController{ maxSpeed, acceleration };
}

void MapEditMap::makeWall(double posX, double posY, unsigned width, unsigned height)
{
	walls_.push_back(new MapEditWall{ posX, posY, width, height});
}

void MapEditMap::makeSpawner(double posX, double posY, unsigned width, unsigned height)
{
	spawners_.push_back(new MapEditSpawner{ posX, posY, width, height});
}

void MapEditMap::makePlayerSpawner(double posX, double posY, unsigned width, unsigned height)
{
	delete playerspawner_;
	playerspawner_=(new MapEditPlayerSpawner{ posX, posY, width, height});
}

MapEditCameraController* MapEditMap::getCameraController()
{
	return CameraController_;
}

std::vector<MapEditWall*>& MapEditMap::getWalls()
{
	return walls_;
}

std::vector<MapEditSpawner*>& MapEditMap::getSpawners()
{
	return spawners_;
}

MapEditPlayerSpawner* MapEditMap::getPlayerSpawner()
{
	return playerspawner_;
}

void MapEditMap::saveMap()
{
	std::string filename{"savedmap.txt"};
	std::ofstream ofs;
	ofs.open(filename);
	
	ofs<<"Playerspawner:"<<std::endl;
	if(playerspawner_!=nullptr)
		ofs<<playerspawner_->getX()<<" "<<playerspawner_->getY()<<" "<<playerspawner_->getWidth()<<" "<<playerspawner_->getHeight()<<std::endl;
		
	ofs<<"Walls:"<<std::endl;
	for(auto x : walls_)
	{
		ofs<<x->getX()<<" "<<x->getY()<<" "<<x->getWidth()<<" "<<x->getHeight()<<std::endl;
	}
	
	ofs<<"Spawners:"<<std::endl;
	for(auto x : spawners_)
	{
		ofs<<x->getX()<<" "<<x->getY()<<" "<<x->getWidth()<<" "<<x->getHeight()<<std::endl;
	}
	ofs.close();
}
void MapEditMap::loadMap()
{
	delete_walls();
	delete_spawners();
	std::string filename{"savedmap.txt"};
	std::string str;
	std::string type;
	double x,y,w,h;
	std::ifstream ifs;
	ifs.open(filename);
	while(getline(ifs,str))
	{
		std::stringstream ss(str);
		std::stringstream ss2(str);
		if(ss>>x>>y>>w>>h)
		{
			if(type == "Playerspawner:")
			{
				makePlayerSpawner(x,y,w,h);
			}
			else if(type == "Walls:")
			{
				makeWall(x,y,w,h);
			}
			else if(type == "Spawners:")
			{
				makeSpawner(x,y,w,h);
			}
		}
		else
		{
			ss2>>type;
		}
	}
	
	
	ifs.close();
}

void MapEditMap::delete_walls()
{
	for(int i{walls_.size()-1}; i>-1; --i)
	{
		delete walls_.at(i);
		walls_.erase( walls_.begin() + i );
	}
}

void MapEditMap::delete_spawners()
{
	for(int i{spawners_.size()-1}; i>-1; --i)
	{
		delete spawners_.at(i);
		spawners_.erase( spawners_.begin() + i );
	}
}