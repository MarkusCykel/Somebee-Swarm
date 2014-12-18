#include "Edit.h"
#include <iostream>
#define SCREEN_FPS 60
#define SCREEN_TICKS_PER_FRAME 1000 / SCREEN_FPS + 1

Edit::Edit(unsigned height, unsigned width, Window& window)
	: map_{height,width}, camera_{ 0, 0, window.getWidth() *3/4, window.getHeight() }, quit_{ false }, gameOver_{false}, window_{window}, intersectiftrue{false}
{
		map_.makeCameraController(10, 10);
		map_.loadBackground("background_tho.jpg", window_.getRenderer());
}

bool Edit::menu()
{
	if( mouseposX >= window_.getWidth()-window_.getWidth()*1/4 ) 
		return true;
	else 
		return false;
}

bool Edit::outofbounds()
{
	if(mouseposX + camera_.x + square.w/2 > map_.getWidth() || mouseposX + camera_.x - square.w/2 < 0 || mouseposY + camera_.y + square.h/2 > map_.getHeight() || mouseposY + camera_.y - square.h/2 < 0)
	{
		return true;
	}
	else 
		return false;
}

void Edit::run(SDL_Event& e)
{
	while(!quit_ && !gameOver_)
	{
		capTimer_.start();

		readInput(e);
		update();
		render();

		int frameTicks = capTimer_.getTicks();
		if( frameTicks < SCREEN_TICKS_PER_FRAME )
		{
			SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
		}
	}
}
	
	
void Edit::readInput(SDL_Event& e)
{
	auto MapEditCameraController = map_.getCameraController();
	
	SDL_GetMouseState( &mouseposX, &mouseposY );
	
	while(SDL_PollEvent(&e) != 0)
	{
		if(e.type == SDL_QUIT || (menu_.get_button().getname()== "Quit" && menu_.get_button().buttonpressed()))
		{
			quit_ = true;
		}
		else if( e.type == SDL_MOUSEBUTTONDOWN  && e.button.button == SDL_BUTTON_LEFT )
		{
			
			if(!menu()&& menu_.get_button().buttonpressed()&& !intersectiftrue)
			{
				if(menu_.get_button().getname()== "Wall")
					map_.makeWall((square.x + square.w/2 ), (square.y + square.h/2), square.w, square.h);
				else if(menu_.get_button().getname()== "Spawner")
					map_.makeSpawner((square.x + square.w/2 ), (square.y + square.h/2), square.w, square.h);
				else if(menu_.get_button().getname()== "PlayerSpawner")
					map_.makePlayerSpawner((square.x + square.w/2 ), (square.y + square.h/2), square.w, square.h);
			}
			if(menu())
				menu_.check_input(mouseposX, mouseposY, menuViewport);
		}
		else if(menu_.get_button().getname()== "Save"&&menu_.get_button().buttonpressed())
		{
			map_.saveMap();
			menu_.get_button().setbuttonpressed(false);
		}
		else if(menu_.get_button().getname()== "Load"&&menu_.get_button().buttonpressed())
		{
			map_.loadMap();
			menu_.get_button().setbuttonpressed(false);
		}
	}

	
	map_.getCameraController()->readInput();
}


void Edit::update()
{
	map_.getCameraController()->update(map_);
	
	square.x = mouseposX + camera_.x ;
	square.y = mouseposY + camera_.y ;
	if(mouseposX + camera_.x - square.w/2 <0)
	{
		square.x = 0;
	}
	else if(mouseposX + camera_.x + square.w/2 > map_.getWidth())
	{
		square.x =  map_.getWidth() - square.w;
	}
	if(mouseposY + camera_.y - square.h/2 < 0)
	{
		square.y = 0;
	}
	else if(mouseposY + camera_.y + square.h/2 > map_.getHeight())
	{
		square.y = map_.getHeight() - square.h;
	}
	square.x = square.x/30*30;
	square.y = square.y/30*30;
	camera_.x = floor(map_.getCameraController()->getX()) - camera_.w/ 2;
    camera_.y = floor(map_.getCameraController()->getY())- camera_.h/ 2;
	
	intersectiftrue = collision();
}

void Edit::render()
{
	SDL_SetRenderDrawColor( window_.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( window_.getRenderer() );
	//Render in the correct viewport
    SDL_RenderSetViewport( window_.getRenderer(), &mapViewport );
	map_.renderBackground(window_.getRenderer(), camera_, camera_.w, camera_.h);
	SDL_Rect renderquad = {square.x - camera_.x, square.y - camera_.y, square.w, square.h};
	auto walls = map_.getWalls();
	
	for( auto i : walls )
	{
		i->render( window_.getRenderer(), camera_);
	}
	
	auto spawners = map_.getSpawners();
	
	for( auto i : spawners )
	{
		i->render( window_.getRenderer(), camera_);
	}
	
	auto player = map_.getPlayerSpawner();
	if(player!=nullptr)
		player->render( window_.getRenderer(), camera_ );
	
	if(menu_.get_button().buttonpressed()&&(menu_.get_button().getname()== "PlayerSpawner" ||menu_.get_button().getname()== "Spawner"||menu_.get_button().getname()== "Wall"))
	{
		SDL_SetRenderDrawBlendMode(window_.getRenderer(),SDL_BLENDMODE_BLEND);
		if(intersectiftrue == true) 
			SDL_SetRenderDrawColor( window_.getRenderer(), 0xFF, 0x00, 0x00, 0x8F );
		else 
			SDL_SetRenderDrawColor( window_.getRenderer(), 0x00, 0xFF, 0x00, 0x8F );
		SDL_RenderFillRect( window_.getRenderer(), &renderquad );
		SDL_SetRenderDrawBlendMode(window_.getRenderer(),SDL_BLENDMODE_NONE);
	}
	
	//Render menu
	SDL_RenderSetViewport( window_.getRenderer(), &menuViewport );
	menu_.render( window_.getRenderer(), menuViewport );
	
	SDL_RenderPresent( window_.getRenderer() );
}


bool Edit::collision()
{
	SDL_Rect tmp2;
	SDL_Rect tmp3 = {square.x + square.w/2, square.y + square.h/2, square.w, square.h};

	auto walls = map_.getWalls();
	auto spawners = map_.getSpawners();
	auto player = map_.getPlayerSpawner();
	for( auto i : walls )
	{
		SDL_Rect tmp{ i->getX(), i->getY(), i->getWidth(), i->getHeight() };
		if(SDL_TRUE == SDL_IntersectRect( & tmp, & tmp3, & tmp2 ))
		{	
			return true;
		}
	}
	for( auto i : spawners )
	{
		SDL_Rect tmp{ i->getX(), i->getY(), i->getWidth(), i->getHeight() };
		if(SDL_TRUE == SDL_IntersectRect( & tmp, & tmp3, & tmp2 ))
		{	
			return true;
		}
	}
	if(player!=nullptr)
	{
		SDL_Rect tmp{ player->getX(), player->getY(), player->getWidth(), player->getHeight() };
		if(SDL_TRUE == SDL_IntersectRect( & tmp, & tmp3, & tmp2 ))
		{	
			return true;
		}
	}
	
	return false;
}