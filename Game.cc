#include "Game.h"
#include "SDL.h"
#include <iostream>

Game::Game(Window& window) : window_{window}, play_{nullptr}, menu_{nullptr}, edit_{nullptr} {}

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

		BUTTON_CODE choice = menu_->run(e);
		
		switch( choice )
		{
			case BUTTON_PLAY:
				if( play_ != nullptr)
				{
					delete play_;
					play_ = nullptr;
				}
				
				play_ = new Play{3000,3000,window_};
				quit_ = play_->run(e);
				
				if( submit_ != nullptr )
				{
					delete submit_;
					submit_ = nullptr;
				}
				
				submit_= new Submit{ window_ };
				
				submit_->run(e);
				break;
				
			case BUTTON_MAP_EDITOR:
				if( edit_ != nullptr)
				{
					delete edit_;
					edit_ = nullptr;
				}
				
				edit_ = new Edit{ 3000, 3000, window_ };
				
				edit_->run(e);
				break;
				
			case BUTTON_SCORE:
				break;
				
			case BUTTON_CREDITS:
				break;
				
			case BUTTON_QUIT:
				quit_ = true;
				break;
				
			default:
				break;
		}
	}
}