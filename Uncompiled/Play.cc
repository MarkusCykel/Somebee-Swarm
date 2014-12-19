#include "Play.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#define SCREEN_FPS 60
#define SCREEN_TICKS_PER_FRAME 1000 / SCREEN_FPS + 1


Play::Play(unsigned height, unsigned width, Window& window)
	: map_{height,width}, camera_{ 0, 0, window.getWidth(), window.getHeight() }, exitGame_{ false }, gameOver_{false}, window_{window}, score_{0}, action_{NONE}
{
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
				map_.makePlayer(x,y,w,h,10,1,20);
			}
			else if(type == "Walls:")
			{
				map_.makeWall(x,y,w,h);
			}
			else if(type == "Spawners:")
			{
				map_.makeSpawner(x,y,w,h,10,1);
			}
		}
		else
		{
			ss2>>type;
		}
		
		if( map_.getPlayer() == nullptr )
			map_.makePlayer(0,0,30,30,10,1,20);
	}
	
	
	ifs.close();
	
	font_ = TTF_OpenFont( "CoolFont.ttf", 28 );
	map_.loadBackground( window_.getRenderer(),"background_tho.jpg" );
	NPC::loadTexture( window_.getRenderer(), "BeeCool.png" );
	Spawner::loadTexture( window_.getRenderer(), "OhBeeHive.png" );
}


ACTION Play::run(SDL_Event& e)
{
	while(action_ == NONE)
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
	
	return action_;
}
	
	
void Play::readInput(SDL_Event& e)
{
	auto player = map_.getPlayer();
	int x ,y;
	static bool LMBDown{false};
	
	while(SDL_PollEvent(&e) != 0)
	{
		if(e.type == SDL_QUIT)
		{
			action_ = EXIT_GAME;
		}
		else if ( e.type == SDL_KEYDOWN )
		{
			if( e.key.keysym.sym == SDLK_ESCAPE )
			{
				action_ = QUIT_GAME;
			}
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
}


void Play::update()
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
	
	if(map_.cleanUp(score_))
	{
		action_ = GAME_OVER;
	}
}


void Play::render()
{
	//clear and render background
	SDL_SetRenderDrawColor( window_.getRenderer(), 0x00, 0x00, 0x00, 0x00 );
	SDL_RenderClear( window_.getRenderer() );
	map_.renderBackground(window_.getRenderer(), camera_, window_.getWidth(), window_.getHeight());
	
	//render entites
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
	
	//render score
	std::ostringstream ss;
	ss << "Score: " << score_;
	std::string text = ss.str();
	SDL_Color textColor = { 0xFF, 0xFF, 0xFF};
	text_.loadFromRenderedText( text, textColor, font_, window_.getRenderer() );
	SDL_Rect renderTarget = { window_.getWidth()/2 - text_.getWidth()/2, 0, text_.getWidth(), text_.getHeight() };
	text_.render(window_.getRenderer(), NULL, &renderTarget);
	
	SDL_RenderPresent( window_.getRenderer() );
}