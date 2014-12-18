#include "Submit.h"

Submit::Submit(Window& window) : window_{window}
{
	SDL_Point button = {window_.getWidth()/2 - BUTTON_WIDTH - 5, window_.getHeight()/2 + 50 };

	buttons_.push_back(new Button{ window.getRenderer(), "SUBMIT", button, BUTTON_SUBMIT });
	button.x += BUTTON_WIDTH + 10;
	
	buttons_.push_back(new Button{ window.getRenderer(), "CANCEL", button, BUTTON_CANCEL });
	
	
	std::string text = "<input nickname>";
	
	TTF_Font* font;
	font = TTF_OpenFont("CoolFont.ttf", 24);
	SDL_Color textColor = { 0x00, 0x00, 0x00};
	textTexture_.loadFromRenderedText( text, textColor, font, window_.getRenderer());
}

Submit::~Submit()
{
	for( auto& i : buttons_ )
	{
		delete i;
		i = nullptr;
	}
}

bool Submit::run( SDL_Event& e )
{
	render();
	
	bool done { false };
	
	while(!done)
	{
		done = readInput(e);
		render();
	}
}

bool Submit::readInput(SDL_Event& e)
{
	bool quit = false;
	
	SDL_StartTextInput();

	bool renderText = false;

	while( SDL_PollEvent( &e ) != 0 )
	{
		if( e.type == SDL_QUIT )
		{
			quit = true;
		}
		else if( e.type == SDL_KEYDOWN )
		{
			if( e.key.keysym.sym == SDLK_BACKSPACE && text_.length() > 0 )
			{

				text_.pop_back();
				renderText = true;
			}
			else if( e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL )
			{
				text_ = SDL_GetClipboardText();
				renderText = true;
			}
		}
		else if( e.type == SDL_TEXTINPUT && text_.length() < 16 )
		{
			if( !(( e.text.text[ 0 ] == 'v' || e.text.text[ 0 ] == 'V' ) && SDL_GetModState() & KMOD_CTRL ) )
			{
				text_ += e.text.text;
				renderText = true;
			}
		}
		else
		{
			for( auto i : buttons_ )
			{
				switch ( i->handleEvent(e) )
				{
					case BUTTON_SUBMIT:
						submitScore();
						return true;
						
					case BUTTON_CANCEL:
						return true;
						
					default:
						break;
				}
			}
		}
	}

	//Rerender text if needed
	if( renderText )
	{
		TTF_Font* font;
		font = TTF_OpenFont("CoolFont.ttf", 24);
		SDL_Color textColor = { 0x00, 0x00, 0x00};
		
		//Text is not empty
		if( text_ != "" )
		{
			textTexture_.loadFromRenderedText( text_, textColor, font, window_.getRenderer());
		}
		//Text is empty
		else
		{
			//Render space texture
			textTexture_.loadFromRenderedText( " ", textColor, font, window_.getRenderer());
		}
	}
	
	//Disable text input
	SDL_StopTextInput();
	
	return false;
}

void Submit::render()
{
	SDL_SetRenderDrawColor( window_.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( window_.getRenderer() );

	for( auto i : buttons_ )
	{
		i->render( window_.getRenderer() );
	}
	
	SDL_Rect renderTarget = { window_.getWidth()/2 - textTexture_.getWidth()/2, window_.getHeight()/2, textTexture_.getWidth(), textTexture_.getHeight() };
	
	textTexture_.render( window_.getRenderer(), NULL, &renderTarget );
	
	SDL_RenderPresent( window_.getRenderer() );
}
		