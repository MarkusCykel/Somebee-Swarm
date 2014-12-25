#include "Menu.h"

Menu::Menu(Window& window) : window_{window}
{
	SDL_Point button = {window_.getWidth()/2 - BUTTON_WIDTH/2, window_.getHeight()/2 };

	buttons_.push_back(new Button{ window.getRenderer(), "PLAY", button, BUTTON_PLAY });
	button.y += 60;
	
	buttons_.push_back(new Button{ window.getRenderer(), "MAP EDITOR", button, BUTTON_MAP_EDITOR });
	
	button.y += 60;
	
	buttons_.push_back(new Button{ window.getRenderer(), "HIGH SCORE", button, BUTTON_SCORE });
	
	button.y += 60;
	
	buttons_.push_back(new Button{ window.getRenderer(), "CREDITS", button, BUTTON_CREDITS });
	
	button.y += 60;
	
	buttons_.push_back(new Button{ window.getRenderer(), "QUIT", button, BUTTON_QUIT });
	
	background_.loadFromFile( window_.getRenderer(), "Logo.png" );
}

Menu::~Menu()
{
	for( auto& i : buttons_ )
	{
		delete i;
		i = nullptr;
	}
}

BUTTON_CODE Menu::run(SDL_Event& e)
{
	render();
	bool done {false};
	
	while( !done )
	{
		done = readInput(e);
	}
	
	return selection_;
}

bool Menu::readInput(SDL_Event& e)
{
	int x ,y;
	
	while(SDL_PollEvent(&e) != 0)
	{
		if(e.type == SDL_QUIT)
		{
			selection_ = BUTTON_QUIT;
			return true;
		}
		for( auto i : buttons_ )
		{
			switch ( i->handleEvent(e) )
			{
				case BUTTON_PLAY:
					selection_ = BUTTON_PLAY;
					return true;
					
				case BUTTON_MAP_EDITOR:
					selection_ = BUTTON_MAP_EDITOR;
					return true;
					
				case BUTTON_SCORE:
					selection_ = BUTTON_SCORE;
					return true;
					
				case BUTTON_CREDITS:
					selection_ = BUTTON_CREDITS;
					return true;
					
				case BUTTON_QUIT:
					selection_ = BUTTON_QUIT;
					return true;
					
				default:
					break;
			}
		}
	}
	
	return false;
}

void Menu::render()
{
	SDL_SetRenderDrawColor( window_.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( window_.getRenderer() );
	
	SDL_Rect renderTarget { window_.getWidth()/2 - background_.getWidth()/2*4/5, window_.getHeight()/2*4/5 - 380, background_.getWidth()*4/5, background_.getHeight()*4/5 };
	background_.render( window_.getRenderer(), NULL, &renderTarget );
	
	for( auto i : buttons_ )
	{
		i->render( window_.getRenderer() );
	}
	
	SDL_RenderPresent( window_.getRenderer() );
}
