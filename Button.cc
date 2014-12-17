#include "Button.h"

//Just a very long constructor
Button::Button(SDL_Renderer* renderer, std::string text, const SDL_Point & button, BUTTON_CODE id, const Uint8 & R , const Uint8 & G, const Uint8 & B, const Uint8 & A)
	: position_{button.x, button.y}, id_{id}, R_{R}, G_{G}, B_{B}, A_{A}
{
	TTF_Font* font;
	font = TTF_OpenFont("CoolFont.ttf", 24);
	SDL_Color textColor = { 0xFF, 0xFF, 0xFF};
	text_.loadFromRenderedText( text, textColor, font, renderer);
}
 
BUTTON_CODE Button::handleEvent(SDL_Event& e)
{
	if ( e.type == SDL_MOUSEBUTTONDOWN )
	{
		//Get mouse pos
		int x, y;
		SDL_GetMouseState (&x, &y);
		//Check if inside button
		bool inside = true;
		
		if ( x < position_.x ) //IF left of button
		{
			inside = false;
		}
		else if( x > position_.x + BUTTON_WIDTH ) //IF right of button
		{
			inside = false;
		}
		else if( y < position_.y ) //IF above
		{
			inside = false;
		}
		else if( y > position_.y + BUTTON_HEIGHT ) //IF below
		{
			inside = false;
		}

		if ( inside )
		{
			return id_;
		}
	}
}

void Button::render(SDL_Renderer* renderer)
{
	SDL_Rect renderTarget = { position_.x, position_.y, BUTTON_WIDTH, BUTTON_HEIGHT };
	SDL_SetRenderDrawColor( renderer, R_, G_, B_, A_ );
	SDL_RenderFillRect( renderer, &renderTarget );
	SDL_Rect text = { 0, 0, text_.getWidth(), text_.getHeight()};
	
	renderTarget.x += renderTarget.w/2 - text.w/2;
	renderTarget.y += renderTarget.h/2 - text.h/2;
	renderTarget.w = text.w;
	renderTarget.h = text.h;
	
	text_.render(renderer, &text, &renderTarget);
}

void Button::setColor(const Uint8 & R, const Uint8 & G, const Uint8 & B, const Uint8 & A )
{
	 R_ = R;
	 G_ = G;
	 B_ = B;
	 A_ = A;
}


void Button::setPosition(int x, int y)
{
	position_.x = x;
	position_.y = y;
}