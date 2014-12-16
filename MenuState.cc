#include "MenuState.h"

MenuState::MenuState(Window& window) : window_{window}
{
	SDL_Rect button { window_.getWidth()/2-100, 400, 200, 50 };
	
	buttons_.push_back(new Button{ button, "button1" });
	
	button.y += 60;
	
	buttons_.push_back(new Button{ button, "button2"});
	
	button.y += 60;
	
	buttons_.push_back(new Button{ button, "button3" });
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
			SDL_GetMouseState( &x, &y );
			SDL_Rect click{x,y,1,1};
			for( auto i : buttons_ )
			{
				SDL_Rect buttonRect = i->getRect();

				if(SDL_HasIntersection(&click, &buttonRect) == SDL_TRUE)
					i->handleEvent(e);
			}
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
