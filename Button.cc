#include "Button.h"

//Just a very long constructor
Button::Button(const SDL_Rect & butt, const Uint8 & R = 0xFF, const Uint8 & G = 0x00, const Uint8 & B = 0x00, const Uint8 & A 0xFF, const bool & press = false ): R_{R},G_{G},B_{B},A_{A},button_{butt},buttonpressed_{press}{};

Button::Button():R_{0xFF},G_{0x00},B_{0x00},A_{0xFF},button_{SDL_Rect temp{ 50, 50, 50, 30}},buttonpressed_{false}{}

void Button::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor( renderer, R_, G_, B_, A_ );
	SDL_RenderFillRect( renderer, &button );
}

void Button::setcolor(const Uint8 & R, const Uint8 & G, const Uint8 & B, const Uint8 & A )
{
	 R_ = R;
	 G_ = G;
	 B_ = B;
	 A_ = A;
}

void setbuttonpressed(const bool & a)
{
	buttonpressed_ = a;
}
