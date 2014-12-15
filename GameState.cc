#include "GameState.h"
#include <iostream>
#define SCREEN_FPS 61
#define SCREEN_TICKS_PER_FRAME 1000 / SCREEN_FPS + 1

GameState::GameState(unsigned height, unsigned width, Window& window)
	: map_{height,width}, camera_{ 0, 0, window.getWidth(), window.getHeight() }, quit_{ false }, gameOver_{false}, window_{window}, score_{0}
{
		map_.makePlayer(250, 250, 30, 30, 10, 1, 15);
		map_.makeSpawner( 0, 0, 30, 30, 8, 1);
		map_.makeSpawner( height-30, width-30, 30, 30, 8, 1);
		map_.makeSpawner( height-30, 0, 30, 30, 8, 1);
		map_.makeSpawner( 0, width-30, 30, 30, 8, 1);
		map_.makeSpawner( 0, width/2, 30, 30, 8, 1);
		map_.makeSpawner( height/2, 0, 30, 30, 8, 1);
		map_.makeWall( 1040, 300, 1, 500);
		map_.makeWall( 840, 300, 1, 490);
		map_.makeWall( 540, 300, 500, 1);
		map_.makeWall( 540, 800, 290, 1);
	//	map_.makeWall( 740, 800, 1, 50);
		//map_.makeWall( 840, 800, 1, 50);
		
		//map_.makeWall( 840, 800, 210, 10);
		//map_.makeWall( 1040, 300, 10, 500);
		
		map_.loadBackground("background_tho.jpg", window_.getRenderer());
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
		std::cout << SCREEN_TICKS_PER_FRAME - frameTicks << std::endl;
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
	
	while(SDL_PollEvent(&e) != 0)
	{
		if(e.type == SDL_QUIT)
		{
			quit_ = true;
		}
		else if( e.type == SDL_MOUSEBUTTONDOWN  && e.button.button == SDL_BUTTON_LEFT )
		{
			LMBDown = true;
			SDL_GetMouseState( &x, &y );
			x = camera_.x + x;
			y = camera_.y + y;
			player->fire(map_,x,y);
		}
		else if( e.type == SDL_MOUSEBUTTONUP  && e.button.button == SDL_BUTTON_LEFT )
		{
			LMBDown = false;
		}
	}
	
	if( LMBDown )
	{
		SDL_GetMouseState( &x, &y );
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
	//std::cout << score_ << std::endl;
}


void GameState::update()
{
	map_.getPlayer()->update(map_);

	camera_.x = map_.getPlayer()->getX() + map_.getPlayer()->getWidth()/2 - camera_.w/2;
    camera_.y = map_.getPlayer()->getY() + map_.getPlayer()->getHeight()/2- camera_.h/2;
	
	auto npcs = map_.getNpcs();
	
	for( auto i : npcs )
	{
		i->update(map_);
	}
	
	auto projectiles = map_.getProjectiles();
	
	for( const auto &i : projectiles )
	{
		i->update(map_);
	}
	
	auto spawners = map_.getSpawners();
	
	for( const auto &i : spawners )
	{
		i->update(map_);
	}
	
	gameOver_ = map_.cleanUp(score_);
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
	
	SDL_RenderPresent( window_.getRenderer() );
}