#include "GameState.h"
#include <iostream>
#define SCREEN_FPS 60
#define SCREEN_TICKS_PER_FRAME 1000 / SCREEN_FPS + 1

GameState::GameState(unsigned height, unsigned width, Window& window)
	: map_{height,width}, camera_{ 0, 0, window.getWidth() *3/4, window.getHeight() }, quit_{ false }, gameOver_{false}, window_{window}
{
		map_.makeCameraController(10, 10);
		map_.loadBackground("background_tho.jpg", window_.getRenderer());
}

bool GameState::menu()
{
	if( mouseposX >= window_.getWidth()-window_.getWidth()*1/4 ) 
		return true;
	else 
		return false;
}

bool GameState::outofbounds()
{
	if(mouseposX + camera_.x > map_.getWidth() || mouseposX + camera_.x < 0 || mouseposY + camera_.y > map_.getHeight() || mouseposY + camera_.y < 0)
	{
		return true;
	}
	else 
		return false;
}

void GameState::run(SDL_Event& e)
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
	
	
void GameState::readInput(SDL_Event& e)
{
	auto CameraController = map_.getCameraController();
	
	SDL_GetMouseState( &mouseposX, &mouseposY );
	
	while(SDL_PollEvent(&e) != 0)
	{
		if(e.type == SDL_QUIT)
		{
			quit_ = true;
		}
		else if( e.type == SDL_MOUSEBUTTONDOWN  && e.button.button == SDL_BUTTON_LEFT )
		{
			if(!menu() && !outofbounds())
				map_.makeWall(mouseposX + camera_.x, mouseposY + camera_.y, 30, 30);
		}
		else if( e.type == SDL_MOUSEBUTTONUP  && e.button.button == SDL_BUTTON_LEFT )
		{
			
		}
	}

	
	map_.getCameraController()->readInput();
}


void GameState::update()
{
	map_.getCameraController()->update(map_);
	
	camera_.x = floor(map_.getCameraController()->getX()) - camera_.w/ 2;
    camera_.y = floor(map_.getCameraController()->getY())- camera_.h/ 2;

}

void GameState::render()
{
	SDL_SetRenderDrawColor( window_.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( window_.getRenderer() );
	
	//Render in the correct viewport
    SDL_RenderSetViewport( window_.getRenderer(), &mapViewport );
	map_.renderBackground(window_.getRenderer(), camera_, camera_.w, camera_.h);
	
	auto walls = map_.getWalls();
	
	for( auto i : walls )
	{
		i->render( window_.getRenderer(), camera_);
	}
	
	SDL_RenderPresent( window_.getRenderer() );
	
	//Render menu
	//SDL_RenderSetViewport( window_.getRenderer(), &menuViewport );
}