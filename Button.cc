#include "Button.h"

//Just a very long constructor
Button::Button(const SDL_Rect & button, const Uint8 & R , const Uint8 & G, const Uint8 & B, const Uint8 & A, const bool & press)
	: button_{button.x, button.y, button.w, button.h}, R_{R},G_{G},B_{B},A_{A},buttonPressed_{press} {};

Button::Button():R_{0xFF},G_{0x00},B_{0x00},A_{0xFF},buttonPressed_{false}
{
	SDL_Rect temp{ 50, 50, 50, 30}; 
	button_ = temp;
}

void handleEvent(SDL_Event& e)
{
}

void Button::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor( renderer, R_, G_, B_, A_ );
	SDL_RenderFillRect( renderer, &button_ );
}

void Button::setColor(const Uint8 & R, const Uint8 & G, const Uint8 & B, const Uint8 & A )
{
	 R_ = R;
	 G_ = G;
	 B_ = B;
	 A_ = A;
}

void Button::setButtonPressed(const bool & a)
{
	buttonPressed_ = a;
}

void Button::setRect(int x, int y, int w, int h)
{
	button_.x = x;
	button_.y = y;
	button_.w = w;
	button_.h = h;
}