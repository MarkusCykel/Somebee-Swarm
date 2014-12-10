#include "GameState.h"
#include <iostream>

GameState::GameState(unsigned height, unsigned width, Window& window)
	: map_{height,width}, camera_{ 0, 0, window.getWidth(), window.getHeight() }, quit_{ false }, window_{window}
{
		map_.makePlayer(250, 250, 20, 20, 5, 1);
		map_.makeSpawner( 100, 354, 30, 30, 2, 1);
		map_.makeSpawner( 700, 354, 30, 30, 2, 1);
		map_.makeSpawner( 900, 354, 15, 15, 2, 1);
		map_.makeSpawner( 200, 500, 13, 13, 2, 1);
		map_.makeSpawner( 300, 354, 11, 11, 2, 1);
		map_.makeSpawner( 1100, 700, 9, 9, 2, 1);
}


void GameState::run()
{
	while(!quit_)
	{
		capTimer_.start();
		
		while(SDL_PollEvent(&e) != 0)
		{
			if(e.type == SDL_QUIT)
			{
				quit_ = true;
			}
		}
		
		readInput();
		update();
		render();

		int frameTicks = capTimer_.getTicks();
		if( frameTicks < 17 )
		{
			SDL_Delay( 17 - frameTicks );
		}
	}
}
	
	
void GameState::readInput()
{
	map_.getPlayer()->readInput();
	
	auto npcs = map_.getNpcs();
	
	for( auto i : npcs )
	{
		i->readInput();
	}
	
	auto projectiles = map_.getProjectiles();
	
	for( auto i : projectiles )
	{
		i->readInput();
	}
}


void GameState::update()
{
	map_.getPlayer()->update();
	
	auto npcs = map_.getNpcs();
	
	for( auto i : npcs )
	{
		i->update();
	}
	
	auto projectiles = map_.getProjectiles();
	
	for( const auto &i : projectiles )
	{
		i->update();
	}
	
	controller_.update(map_);
	
	camera_.x = floor(map_.getPlayer()->getX()) - camera_.w/ 2;
    camera_.y = floor(map_.getPlayer()->getY())- camera_.h/ 2;
}


void GameState::render()
{
	SDL_SetRenderDrawColor( window_.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( window_.getRenderer() );
	
	map_.getPlayer()->render( window_.getRenderer(), camera_);
	
	auto npcs = map_.getNpcs();
	
	for( auto i : npcs )
	{
		i->render( window_.getRenderer(), camera_);
	}
	
	auto projectiles = map_.getProjectiles();
	
	for( auto i : projectiles )
	{
		i->render( window_.getRenderer(), camera_);
	}
	
	SDL_RenderPresent( window_.getRenderer() );
}