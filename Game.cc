#include "Game.h"
#include "SDL.h"
#include <iostream>

Game::Game(Window& window) : window_{window}, play_{nullptr}, menu_{nullptr} {}

bool Game::run()
{
	while( !quit_ )
	{
		if( menu_ != nullptr )
		{
			delete menu_;
			menu_ = nullptr;
		}
		
		menu_ = new Menu{window_};

		SELECTION choice = menu_->run(e);
		
		switch( choice )
		{
			case GAME:
				if( play_ != nullptr)
				{
					delete play_;
					play_ = nullptr;
				}
				
				play_ = new Play{3000,3000,window_};
				quit_ = play_->run(e);
				break;
			case MAP_EDITOR:
				break;
			case SCORE:
				break;
			case CREDITS:
				break;
			case QUIT:
				quit_ = true;
				break;
				
			default:
				break;
		}
	}
}