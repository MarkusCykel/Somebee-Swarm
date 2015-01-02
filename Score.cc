#include "Score.h"

Score::Score(Window& window)
{
	loadscores("score.txt");
	window_ = window;
	
	SDL_Point button = {window_.getWidth()/2 - BUTTON_WIDTH/2, window_.getHeight() - window_.getHeight()/6 };

	buttons_.push_back(new Button{ window_.getRenderer(), "BACK", button, BUTTON_BACK });

}

Score::~Score()
{
	for( auto& i : buttons_ )
	{
		delete i;
		i = nullptr;
	}
}

void Score::loadscores(const std::string & path)
{
	std::ifstream ifs(path);
	std::string str;
	unsigned un;
	
	while(ifs>>str>>un)
	{
		scores_.insert(std::pair<unsigned, std::string>(un,str));
	}
	ifs.close();
}

BUTTON_CODE Score::run( SDL_Event& e )
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

void Score::render()
{
	SDL_SetRenderDrawColor( window_.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( window_.getRenderer() );

	for( auto i : buttons_ )
	{
		i->render( window_.getRenderer() );
	}
	
    TTF_Font* font;
	font = TTF_OpenFont("CoolFont.ttf", 30);
	SDL_Color textColor = { 0x00, 0x00, 0x00};

	int scoreboardstart = text_.getHeight()*2;
	
	std::string header{"Position Name Score"};
	text_.loadFromRenderedText( header, textColor, font, window_.getRenderer());
	SDL_Rect renderTarget = { window_.getWidth()/2 - text_.getWidth()/2, scoreboardstart, text_.getWidth(), text_.getHeight()};
	text_.render( window_.getRenderer(), NULL, &renderTarget );
	
	scoreboardstart += text_.getHeight();
	
	unsigned a{1};

	for (auto it = scores_.rbegin(); it != scores_.rend(); ++it)
	{
		std::stringstream ss;
		std::string tmp {(*it).second};
		tmp.resize(10,' ');
		ss << std::setw(2) << a <<". " << std::left << tmp << " " << (*it).first;
		std::string str = ss.str();
		text_.loadFromRenderedText( str, textColor, font, window_.getRenderer());
		SDL_Rect renderTarget = { window_.getWidth()/2 - text_.getWidth()/2, scoreboardstart + text_.getHeight()* a, text_.getWidth(), text_.getHeight()};
		text_.render( window_.getRenderer(), NULL, &renderTarget );
		
		++a;
	}
	
	SDL_RenderPresent( window_.getRenderer() );
	
	TTF_CloseFont( font );
}

bool Score::readInput(SDL_Event& e)
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











