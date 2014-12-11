#include "GameState.h"
#include <iostream>
#define SCREEN_FPS 60
#define SCREEN_TICKS_PER_FRAME 1000 / SCREEN_FPS + 1

GameState::GameState(unsigned height, unsigned width, Window& window)
	: map_{height,width}, camera_{ 0, 0, window.getWidth(), window.getHeight() }, quit_{ false }, window_{window}
{
		map_.makePlayer(250, 250, 20, 20, 10, 10);
		map_.makeSpawner( 100, 354, 30, 30, 2, 1);
		map_.makeSpawner( 700, 354, 30, 30, 2, 1);
		map_.makeSpawner( 900, 354, 15, 15, 2, 1);
		map_.makeSpawner( 200, 500, 13, 13, 2, 1);
		map_.makeSpawner( 300, 354, 11, 11, 2, 1);
		map_.makeSpawner( 1100, 700, 9, 9, 2, 1);
		map_.loadBackground("background_tho.jpg", window_.getRenderer());
}


void GameState::run(SDL_Event& e)
{
	while(!quit_)
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
	auto player = map_.getPlayer();
	
	int x ,y;
	static bool LMBDown{false};
	SDL_GetMouseState( &x, &y );
	
	while(SDL_PollEvent(&e) != 0)
	{
		if(e.type == SDL_QUIT)
		{
			quit_ = true;
		}
		else if( e.type == SDL_MOUSEBUTTONDOWN  && e.button.button == SDL_BUTTON_LEFT )
		{
			x = camera_.x + x;
			y = camera_.y + y;
			player->fire(map_,x,y);
			LMBDown = true;
		}
		else if( e.type == SDL_MOUSEBUTTONUP  && e.button.button == SDL_BUTTON_LEFT )
		{
			LMBDown = false;
		}
	}
	
	if( LMBDown )
	{
		x = camera_.x + x;
		y = camera_.y + y;
		player->fire(map_,x,y);
	}
	
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
	
	auto spawners = map_.getSpawners();
	
	for( const auto &i : spawners )
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
	
	map_.renderBackground(window_.getRenderer(), camera_, window_.getWidth(), window_.getHeight());
	
	auto projectiles = map_.getProjectiles();
	
	for( auto i : projectiles )
	{
		i->render( window_.getRenderer(), camera_);
	}
	
	map_.getPlayer()->render( window_.getRenderer(), camera_);
	
	auto npcs = map_.getNpcs();
	
	for( auto i : npcs )
	{
		i->render( window_.getRenderer(), camera_);
	}
	
	SDL_RenderPresent( window_.getRenderer() );
}