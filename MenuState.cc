#include "MenuState.h"

MenuState::MenuState(Window& window) : window_{window}
{
	SDL_Rect button { window_.getWidth()/2, 400, 200, 50 };
	
	buttons_.push_back(new Button{ button });
	
	button.y += 60;
	
	buttons_.push_back(new Button{ button });
	
	button.y += 60;
	
	buttons_.push_back(new Button{ button });
	
	
}

bool MenuState::run(SDL_Event& e)
{
	while(!quit_)
	{
		readInput(e);
		update();
		render();
	}
	
	return true;
}

void MenuState::readInput(SDL_Event& e)
{
	int x ,y;

	while(SDL_PollEvent(&e) != 0)
	{
		if(e.type == SDL_QUIT)
		{
			quit_ = true;
		}
		else if( e.type == SDL_MOUSEBUTTONDOWN  && e.button.button == SDL_BUTTON_LEFT )
		{
		}
		else if( e.type == SDL_MOUSEBUTTONUP  && e.button.button == SDL_BUTTON_LEFT )
		{
		}
	}
}

void MenuState::update()
{
	
}

void MenuState::render()
{
	SDL_SetRenderDrawColor( window_.getRenderer(), 0x00, 0x00, 0x00, 0x00 );
	SDL_RenderClear( window_.getRenderer() );
	
	for( auto i : buttons_ )
	{
		i->render(window_.getRenderer());
	}
	
	SDL_RenderPresent( window_.getRenderer() );
}
