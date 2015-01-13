#include "Credit.h"

Credit::Credit(Window& window)
{
	window_ = window;
	
	SDL_Point button = {window_.getWidth()/2 - BUTTON_WIDTH/2, window_.getHeight() - window_.getHeight()/6 };

	buttons_.push_back(new Button{ window_.getRenderer(), "BACK", button, BUTTON_BACK });
	
	
	credits_.push_back("People who helped us.");
}

Credit::~Credit()
{
	for( auto& i : buttons_ )
	{
		delete i;
		i = nullptr;
	}
}

BUTTON_CODE Credit::run( SDL_Event& e )
{
	render();
	
	bool done { false };
	
	while(!done)
	{
		done = readInput(e);
		render();
	}
	
	return selection_;
}

void Credit::render()
{
	SDL_SetRenderDrawColor( window_.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( window_.getRenderer() );

	for( auto i : buttons_ )
	{
		i->render( window_.getRenderer() );
	}
	
    TTF_Font* font;
	font = TTF_OpenFont("CoolFont.ttf", 50);
	SDL_Color textColor = { 0x00, 0x00, 0x00};
	
	
	std::string header{"Credits to:"};
	text_.loadFromRenderedText( header, textColor, font, window_.getRenderer());
	SDL_Rect renderTarget = { window_.getWidth()/2 - text_.getWidth()/2, text_.getHeight(), text_.getWidth(), text_.getHeight()};
	text_.render( window_.getRenderer(), NULL, &renderTarget );
	TTF_CloseFont( font );
	int headerheight{text_.getHeight()};
	
	font = TTF_OpenFont("CoolFont.ttf", 30);
	
	for(auto x : credits_)
	{
		int a{2};
		text_.loadFromRenderedText( x, textColor, font, window_.getRenderer());
		SDL_Rect renderTarget = { window_.getWidth()/2 - text_.getWidth()/2, headerheight + text_.getHeight()*a, text_.getWidth(), text_.getHeight()};
		text_.render( window_.getRenderer(), NULL, &renderTarget );
		a++;
	}
	
	
	SDL_RenderPresent( window_.getRenderer() );
	
	TTF_CloseFont( font );
}

bool Credit::readInput(SDL_Event& e)
{
	bool quit = false;
	while( SDL_PollEvent( &e ) != 0 )
	{
		if( e.type == SDL_QUIT )
		{
			selection_ = BUTTON_QUIT;
			return true;
		}
		else
		{
			for( auto i : buttons_ )
			{
				switch ( i->handleEvent(e) )
				{
					case BUTTON_BACK:
						selection_ = BUTTON_BACK;
						return true;
	
					default:
						break;
				}
			}
		}
	}

	
	return false;
}











